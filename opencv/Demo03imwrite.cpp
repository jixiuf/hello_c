//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_COLOR);
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }


  cv::namedWindow("winname",WINDOW_AUTOSIZE);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("winname", originMat);

  // write to file
  cv::imwrite("out.png", originMat);
  waitKey(0);
  return 0;
}
