#ifndef CVPROJECTV1_0_FACEDETECT_H
#define CVPROJECTV1_0_FACEDETECT_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define DETECT_BUFFER_SIZE 0x20000

using namespace cv;

Mat picFaceDetect(Mat &image,int accuracy);
void vidFaceDetectAndSave(VideoCapture &vid,String savedFileName,int accuracy=0);
Mat picFaceDetect(Mat &image);
Mat picFaceBlur(Mat &image);
void vidFaceBlurAndSave(VideoCapture &vid,String savedFileName);

#endif //CVPROJECTV1_0_FACEDETECT_H