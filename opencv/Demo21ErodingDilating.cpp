//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
// Eroding 侵蚀  and Dilating膨胀

using namespace std;
using namespace cv;
Mat src, target;
int erosion_ele=0;
int erosion_size=0;

int max_eles=3;
int max_kernel_size=21;

int dilation_ele=0;
int dilation_size=0;

void erosion(int ,void*);
void dilation(int,void*);

int main(int argc, char *argv[])
{

  src=imread("in_color.png");
  if(src.empty()){
    exit(-1);
  }
  namedWindow("win_erosion",WINDOW_NORMAL);
  namedWindow("win_dilate",WINDOW_NORMAL);
  cvMoveWindow( "win_dilate", src.cols, 0 );

  /// Create Erosion Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "win_erosion",
                  &erosion_ele, max_eles,
                  erosion );

  createTrackbar( "Kernel size:\n 2n +1", "win_erosion",
                  &erosion_size, max_kernel_size,
                  erosion );

  /// Create Dilation Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "win_dilation",
                  &dilation_ele, max_eles,
                  dilation );

  createTrackbar( "Kernel size:\n 2n +1", "win_dilation",
                  &dilation_size, max_kernel_size,
                  dilation );

  erosion(0,0);
  dilation(0,0);
  waitKey(0);
  return 0;

}
// 两个未有到的参数是因为createTrackbar 接口要求
void erosion(int ,void*){
  int erosion_type;
  if (erosion_ele==0){
    erosion_type=MORPH_RECT;    // morph 形态
  }else if (erosion_ele==1){
    erosion_type=MORPH_CROSS;
  }else{
    erosion_type=MORPH_ERODE;
  }
  Mat ele =getStructuringElement(erosion_type,
                                 Size(2*erosion_size+1,2*erosion_size+1),
                                 Point(erosion_size,erosion_size));
  erode(src,target,ele);
  imshow("win_erosion",target);
}

// 两个未有到的参数是因为createTrackbar 接口要求
void dilation(int ,void*){
  int dilation_type;
  if (dilation_ele==0){
    dilation_type=MORPH_RECT;    // morph 形态
  }else if (dilation_ele==1){
    dilation_type=MORPH_CROSS;
  }else{
    dilation_type=MORPH_ERODE;
  }
  Mat ele =getStructuringElement(dilation_type,
                                 Size(2*dilation_size+1,2*dilation_size+1),
                                 Point(dilation_size,dilation_size));
  dilate(src,target,ele);
  imshow("win_dilate",target);
}
