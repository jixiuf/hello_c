//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

// 模糊化处理
// blurring or smooting
// 主要作用是 去除一些干扰信息
// 最普遍的做法 是 linear filter
// http://docs.opencv.org/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html#smoothing
// http://blog.csdn.net/mlkiller/article/details/8782787
// 均值模糊(box blur) 高斯模糊（gaussian blur)  中值模糊(media blur) 二值模糊(bilateral blur)
// box
// Gaussian
// median
// Bilateral
using namespace std;
using namespace cv;

// 以下代码演示 box blur
int main(int argc, char *argv[]){
  namedWindow("win",WINDOW_NORMAL);

  Mat origin  = imread("in_color.png",CV_LOAD_IMAGE_COLOR);
  Mat boxblured[30];
  if (origin.empty()){
    std::cout << "image doesnot exists" << std::endl;
    exit(-1);
  }
  for (int i = 1; i < 30; ++i){
    // Size( w,h ): Defines the size of the kernel to be used ( of width w
    // pixels and height h pixels)

    // Point(-1, -1): Indicates where the anchor point (the pixel evaluated) is
    // located with respect to the neighborhood. If there is a negative value,
    // then the center of the kernel is considered the anchor point.
    blur(origin,boxblured[i],Size(i,i),Point(-1,-1));
    stringstream s;
    s<<"win"<<i;
    namedWindow(s.str(),WINDOW_NORMAL);
    imshow(s.str(),boxblured[i]);

  }

  imshow("win",origin);
  waitKey(0);
  return 0;
}
