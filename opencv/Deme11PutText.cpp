//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// 画 点线 圆 等图形
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  RNG random;                   //随机数

  string str( "hello");
  Mat m = Mat::zeros(400,400,CV_8UC3);
  int fontFace=random.uniform(0, 8);
  double fontScale=random.uniform(0, 100)*0.05+0.1; // [0.1 ,5.1]
  Point bottom_left= Point(20,200);
  cv::putText(m, str,bottom_left,  fontFace,  fontScale, Scalar(255,0,0) );
  cv::namedWindow("win");
  cv::imshow("win",m);
  cv::waitKey(0);
  return 0;
}
