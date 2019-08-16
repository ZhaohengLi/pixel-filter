#include "faceDetect.h"
#include "facedetectcnn.h"
#include "rectBlur.h"

Mat picFaceDetect(Mat &image, int accuracy){
    Mat result_cnn=image.clone();

    int * pResults = NULL;
    //pBuffer is used in the detection functions.
    //If you call functions in multiple threads, please create one buffer for each thread!
    unsigned char *pBuffer=(unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if(!pBuffer){
        fprintf(stderr, "Can not alloc buffer.\n");
        return result_cnn;
    }

    ///////////////////////////////////////////
    // CNN face detection
    // Best detection rate
    //////////////////////////////////////////
    //!!! The input image must be a BGR one (three-channel) instead of RGB
    //!!! DO NOT RELEASE pResults !!!
    pResults = facedetect_cnn(pBuffer, (unsigned char*)(image.ptr(0)),image.cols,image.rows,(int)image.step);

    printf("%d faces detected.\n", (pResults ? *pResults : 0));

    //print the detection results
    for(int i = 0; i < (pResults ? *pResults : 0); i++){
        short * p = ((short*)(pResults+1))+142*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];
        int confidence = p[4];
        int angle = p[5];

        if(confidence >= accuracy){
            printf("face_rect=[%d, %d, %d, %d], confidence=%d, angle=%d\n", x,y,w,h,confidence, angle);
            rectangle(result_cnn, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
        }
    }

    //release the buffer
    free(pBuffer);

    return result_cnn;
}

void vidFaceDetectAndSave(VideoCapture &vid,String savedFileName, int accuracy){
    int vidWidth=(int)vid.get(CAP_PROP_FRAME_WIDTH);
    int vidHeight=(int)vid.get(CAP_PROP_FRAME_HEIGHT);
    int vidRate=(int)vid.get(CAP_PROP_FPS);
    int vidFourcc=(int)vid.get(CAP_PROP_FOURCC);

    VideoWriter wri(savedFileName,vidFourcc,vidRate,Size(vidWidth,vidHeight));
    if(!wri.isOpened()){ printf("VideoWriter failed to open!\n");return; }

    vid.set(CAP_PROP_POS_FRAMES,0);
    Mat frame;
    Mat afterFaceDetect;
    while(true){
        vid>>frame;
        if(frame.empty()) break;
        if(accuracy==0) afterFaceDetect=picFaceDetect(frame);
        else afterFaceDetect=picFaceDetect(frame,accuracy);
        wri<<afterFaceDetect;
    }
    return;
}

void vidFaceBlurAndSave(VideoCapture &vid,String savedFileName){
    int vidWidth=(int)vid.get(CAP_PROP_FRAME_WIDTH);
    int vidHeight=(int)vid.get(CAP_PROP_FRAME_HEIGHT);
    int vidRate=(int)vid.get(CAP_PROP_FPS);
    int vidFourcc=(int)vid.get(CAP_PROP_FOURCC);

    VideoWriter wri(savedFileName,vidFourcc,vidRate,Size(vidWidth,vidHeight));
    if(!wri.isOpened()){ printf("VideoWriter failed to open!\n");return; }

    vid.set(CAP_PROP_POS_FRAMES,0);
    Mat frame;
    Mat afterFaceBlur;
    while(true){
        vid>>frame;
        if(frame.empty()) break;
        afterFaceBlur=picFaceBlur(frame);
        wri<<afterFaceBlur;
    }
    return;
}

Mat picFaceDetect(Mat &image){
    CascadeClassifier faceHaar = CascadeClassifier("./CascadeClassifierFiles/haarcascade_frontalface_default.xml");
    vector<Rect> faces;
    Mat result=image.clone();
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    faceHaar.detectMultiScale(gray,faces);
    for(size_t i=0; i<faces.size(); i++) rectangle(result,Point(faces[i].x,faces[i].y),Point(faces[i].x+faces[i].width,faces[i].y+faces[i].height),Scalar(0,255,0));
    return result;
}

Mat picFaceBlur(Mat &image){
    CascadeClassifier faceHaar = CascadeClassifier("./CascadeClassifierFiles/haarcascade_frontalface_default.xml");
    vector<Rect> faces;
    Mat result=image.clone();
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    faceHaar.detectMultiScale(gray,faces);
    for(size_t i=0; i<faces.size(); i++){
        //将人脸矩形边长扩大为原来的1.5倍进行模糊
        Point pt1=Point(max(0,int(faces[i].x-faces[i].width/4)),max(0,int(faces[i].y-faces[i].height/4)));
        Point pt2=Point(min(image.cols,int(pt1.x+faces[i].width*3/2)),min(image.rows,int(pt1.y+faces[i].height*3/2)));
        picRectBlur(result,pt1,pt2);
    }
    return result;
}
