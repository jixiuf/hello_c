//  -*- coding:utf-8 -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // 从文件读一个img ,
  Mat originMat  = cv::imread("/Users/jishuuhou/Pictures/m2w500hq85lt_original_XfKB_1b7d000041351191.jpg",CV_LOAD_IMAGE_COLOR);
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  // 截取某一范围内的图片
  Mat B(originMat,Rect(10,10,400,400));
  cv::namedWindow("rect",WINDOW_AUTOSIZE);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("rect", B);


  // 截取某一范围内的图片
  // using row and column boundaries
  //  originMat(Range::all(),Range(1,30)); 取 originMat 的所有行，  [1-30) 列  包括1 不包括30
  // Range 应该是一个范围，  从一个点到另一个点 ， 两个这样的range就划定了一个矩形
  Mat C= originMat(Range::all(),Range(1,30));
  cv::namedWindow("range",WINDOW_AUTOSIZE);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("range", C);


  //  originMat(Range(1,3),Range::all()); 取 originMat  [1-3) 行 包括1 不包括3 ，Range::all()所有列
  Mat D= originMat(Range(1,100),Range::all());
  cv::namedWindow("range2",WINDOW_AUTOSIZE);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("range2", D);

  std::cout << D << std::endl;
  // Met 分为header和data 部分，
  // A(B) A=B , Mat B(originMat,Rect(10,10,400,400)), 等 只是header不同，  其data 指向同一个地方 ，通过引用计数来决定何时清空data内存
  // A=B.clone() ,or A=copeTo(B) ，则会 复制data部分
  cv::waitKey(0);
  return 0;
}
