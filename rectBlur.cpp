#include "rectBlur.h"

void picRectBlur(Mat &img,Range rows,Range cols){
    //TODO 检查传入参数合法性
    Mat target = img(rows,cols);
    GaussianBlur(target,target,Size(299,299),0,0);
    return;
}

void picRectBlur(Mat &img,Point pt1,Point pt2){
    picRectBlur(img,Range(pt1.y,pt2.y),Range(pt1.x,pt2.x));
}

void checkPicRectBlur(){
    Mat img = imread("./BlurFiles/THU.jpg");
    picRectBlur(img,Range(300,500),Range(300,500));

    imshow("afterBlur",img);
    waitKey(0);
    return;
}

void vidRectBlurAndSave(VideoCapture &vid,Range rows,Range cols,String savedFileName){
    int vidWidth=(int)vid.get(CAP_PROP_FRAME_WIDTH);
    int vidHeight=(int)vid.get(CAP_PROP_FRAME_HEIGHT);
    int vidRate=(int)vid.get(CAP_PROP_FPS);
    int vidFourcc=(int)vid.get(CAP_PROP_FOURCC);

    VideoWriter wri(savedFileName,vidFourcc,vidRate,Size(vidWidth,vidHeight));
    if(!wri.isOpened()){ printf("VideoWriter failed to open!\n");return; }

    vid.set(CAP_PROP_POS_FRAMES,0);
    Mat frame;
    while(true){
        vid>>frame;
        if(frame.empty()) break;
        picRectBlur(frame,rows,cols);
        wri<<frame;
    }
    return;
}

void vidRectBlurAndSave(VideoCapture &vid,Point pt1,Point pt2,String savedFileName){
    vidRectBlurAndSave(vid,Range(pt1.y,pt2.y),Range(pt1.x,pt2.x),savedFileName);
}

void checkVidRectBlurAndSave(){
    VideoCapture vid("./BlurFiles/sample.avi");//(width*height)1920*1080 (fps)29 (fourcc)828601953
    if(!vid.isOpened()){ printf("Open video failed!\n");return; }

    vidRectBlurAndSave(vid,Range(200,800),Range(200,1700),"./BlurFiles/sampleAfterBlur.avi");
    return;
}