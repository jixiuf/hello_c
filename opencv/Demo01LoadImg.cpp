//  -*- coding:utf-8-unix -*-
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

  // CV_LOAD_IMAGE_GRAYSCALE灰色图 channel=1
  // rgb 图channel =3

  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_COLOR);

  if(originMat.empty())                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  // depth
  // The method returns the identifier of the matrix element depth (the type of each individual channel).
  // For example, for a 16-bit signed element array, the method returns CV_16S . A complete list of
  // matrix types contains the following values:
  // -   CV_8U=0 - 8-bit unsigned integers ( 0..255 )
  // -   CV_8S=1 - 8-bit signed integers ( -128..127 )
  // -   CV_16U=2 - 16-bit unsigned integers ( 0..65535 )
  // -   CV_16S=3 - 16-bit signed integers ( -32768..32767 )
  // -   CV_32S=4 - 32-bit signed integers ( -2147483648..2147483647 )
  // -   CV_32F=5 - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
  // -   CV_64F=6 - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
  std::cout << "depth="<<originMat.depth() << std::endl;

  // channel
  //当以CV_LOAD_IMAGE_GRAYSCALE 读取时， channels()=1
  std::cout << "channels=" <<originMat.channels()<< std::endl;

  std::cout << "type="<<originMat.type() <<" CV_MAKETYPE="<<CV_MAKETYPE(originMat.depth(),originMat.channels())<< std::endl;
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
