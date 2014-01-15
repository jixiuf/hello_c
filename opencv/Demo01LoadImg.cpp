//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // CV_LOAD_IMAGE_ANYDEPTH - If set, return 16-bit/32-bit image when the input
  //                          has the corresponding depth, otherwise convert it to 8-bit.
  // CV_LOAD_IMAGE_COLOR -    If set, always convert image to the color one
  // CV_LOAD_IMAGE_GRAYSCALE - If set, always convert image to the grayscale

  // 从文件读一个img ,
  Mat originMat  = cv::imread("C:/in.jpg",CV_LOAD_IMAGE_COLOR);
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  // 启动一个窗口，窗口大小 自动调整

  // WINDOW_NORMAL If this is set, the user can resize the window (no constraint).
  // WINDOW_AUTOSIZE If this is set, the window size is automatically adjusted to fit the displayed image (see imshow() ), and you cannot change the window size manually.
  // WINDOW_OPENGL If this is set, the window will be created with OpenGL support.

  cv::namedWindow("winname",WINDOW_AUTOSIZE);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("winname", originMat);
  // Wait for a keystroke in the window
  cv::waitKey(0);               // 无限等待，直到按下某key后才退出
  return 0;
}
