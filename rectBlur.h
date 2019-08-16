#ifndef CVPROJECTV1_0_RECTBLUR_H
#define CVPROJECTV1_0_RECTBLUR_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void picRectBlur(Mat &img,Range rows,Range cols);
void picRectBlur(Mat &img,Point pt1,Point pt2);
void checkPicRectBlur();
void vidRectBlurAndSave(VideoCapture &vid,Range rows,Range cols,String savedFileName);
void vidRectBlurAndSave(VideoCapture &vid,Point pt1,Point pt2,String savedFileName);
void checkVidRectBlurAndSave();

#endif //CVPROJECTV1_0_RECTBLUR_H
