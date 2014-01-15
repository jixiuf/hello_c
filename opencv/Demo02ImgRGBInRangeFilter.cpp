//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
// cv::inRange对图片进行灰色过滤
using namespace cv;
using namespace std;
// 加载一个img ,然后对其RGB 进行一定的过滤
int main( int argc, char** argv )
{
  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_COLOR);
  Mat modifiedMat  ;
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  cv::namedWindow("origin",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("origin", originMat);

  // 只显示 Scalar 两个参数 范围之间的 RGB,
  // 可以对比原图与经此处理后的图片进行对比
  // 此函数 可以实现 以原图为背景的模糊背景
  cv::inRange(originMat, cv::Scalar(00,0,10),cv::Scalar(100,100,256), modifiedMat);
  cv::namedWindow("modified",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("modified", modifiedMat);
  // Wait for a keystroke in the window
  cv::waitKey(0);               // 无限等待，直到按下某key后才退出
  return 0;
}
