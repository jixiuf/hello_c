//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// 两张图片进行叠加
//   cv::addWeighted(imageROI, alpha, originMat2, beta, gama, output);
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

  double alpha=0.3;
  double beta=1-alpha;
  double gama=0.0;
  // 最后一个参数 是输入对象 ，依然指定为imageROI ,则改变后的结果会存到imageROI
  // 而imageROI 是originMat的一个局部， 所以originMat也会跟着改变
  // 再次展现一下originMat,就可以看到叠加后的效果
  cv::addWeighted(imageROI, alpha, originMat2, beta, gama, imageROI);

  cv::namedWindow("weighted",WINDOW_NORMAL);
   // 在这个窗口中 显示上面加载的img
  cv::imshow("weighted", originMat);


  cv::waitKey(0);
  return 0;
}
