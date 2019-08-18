#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "rectBlur.h"
#include "faceDetect.h"

using namespace cv;
using namespace std;
void cutVid();
void splitVid();
void blurAccordingToFile();

int main() {
    blurAccordingToFile();
//    splitVid();
//    cutVid();
//    checkPicRectBlur();
//    checkVidRectBlurAndSave();
//
//    Mat img=imread("./FaceDetectFiles/face1.jpg");
//    imshow("MyWindow",picFaceBlur(img));
//    waitKey(0);
//
//    VideoCapture vid("./FaceDetectFiles/sample.avi");
//    vidFaceBlurAndSave(vid,"./FaceDetectFiles/blur.avi");

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

void splitVid(){
    VideoCapture vid("/Users/lizhaoheng/Dropbox/Work/SRT2/Context&Episodic_Memory/Video_Clips_Materials/Mandy_PNAS_Dataset/Exp1_baseline/Exp1_006_baseline.mp4");
    if(!vid.isOpened()){ printf("Open video failed!\n");return; }
    vid.set(CAP_PROP_POS_FRAMES,200);
    Mat frame;
    for(int i = 0; i < 300; i++){
        vid>>frame;
        String fileName = "./Splitfiles/"+to_string(i)+".jpg";
        imwrite(fileName, frame);
    }
    return;
}

void blurAccordingToFile(){
    for(int i=500; i<501; i++) {
        String imageFileName =
                "/Users/lizhaoheng/Dropbox/Work/CLionProjects/CVProjectV1.0/cmake-build-debug/SplitFiles/" +
                to_string(i) + "_resize.jpg";
        String markFileName =
                "/Users/lizhaoheng/Dropbox/Work/CLionProjects/CVProjectV1.0/cmake-build-debug/SplitFiles/" +
                to_string(i) + "_mark.txt";
        Mat image = imread(imageFileName);
        ifstream markFile;
        markFile.open(markFileName);
        while (!markFile.eof()) {
            int row, col_s, col_e;
            markFile >> row;
            markFile >> col_s;
            markFile >> col_e;
            picRectBlur(image, Range(row, row+1), Range(col_s, col_e+1));
        }
        imwrite("/Users/lizhaoheng/Dropbox/Work/CLionProjects/CVProjectV1.0/cmake-build-debug/SplitFiles/" +
                to_string(i) + "_blur.jpg", image);
    }
}
