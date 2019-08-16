#include <iostream>
#include <opencv2/opencv.hpp>
#include "rectBlur.h"
#include "faceDetect.h"

using namespace cv;

void cutVid();

int main() {
//    cutVid();
//    checkPicRectBlur();
//    checkVidRectBlurAndSave();
//
//    Mat img=imread("./FaceDetectFiles/face1.jpg");
//    imshow("MyWindow",picFaceBlur(img));
//    waitKey(0);
//
    VideoCapture vid("./FaceDetectFiles/sample.avi");
    vidFaceBlurAndSave(vid,"./FaceDetectFiles/blur.avi");

    return 0;
}

void cutVid(){
    VideoCapture vid("/Users/lizhaoheng/Downloads/Exp1_006_baseline.mp4");
    if(!vid.isOpened()){ printf("Open video failed!\n");return; }

    int vidWidth=(int)vid.get(CAP_PROP_FRAME_WIDTH);
    int vidHeight=(int)vid.get(CAP_PROP_FRAME_HEIGHT);
    int vidFps=(int)vid.get(CAP_PROP_FPS);
    int vidFourcc=(int)vid.get(CAP_PROP_FOURCC);

    VideoWriter wri("./FaceDetectFiles/sample.avi",vidFourcc,vidFps,Size(vidWidth,vidHeight));
    if(!wri.isOpened()){ printf("VideoWriter failed to open!\n");return; }

    vid.set(CAP_PROP_POS_FRAMES,200);
    Mat frame;
    for(int i = 0; i < 300; i++){
        vid>>frame;
        wri<<frame;
    }
    return;
}
