//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// 两张图片进行叠加
// originMat2.copyTo(imageROI);
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png");
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  Mat originMat2  = cv::imread("in_color2.png");
  if(! originMat2.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  cv::namedWindow("origin1",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("origin1", originMat);

  cv::namedWindow("origin2",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("origin2", originMat2);

  // 这里需要保证originMat 的大小要比originMat2的大， 这样才能
  // 从originMat里截取 大小与originMat2相同的区域
  Mat imageROI=originMat(cv::Rect(0,0,originMat2.cols,originMat2.rows));                 // region of interest

  originMat2.copyTo(imageROI);

  cv::namedWindow("copyto",WINDOW_NORMAL);
   // 在这个窗口中 显示上面加载的img
  cv::imshow("copyto", originMat);


  cv::waitKey(0);
  return 0;
}
