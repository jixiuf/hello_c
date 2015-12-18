//  -*- coding:utf-8-unix -*-
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// 画 点线 圆 等图形
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  RNG random;                   //随机数

  string str( "hello");
  int width=400;                // cols
  int height=300;               // rows
  Mat m = Mat::zeros(height,width,CV_8UC3);
  int fontFace=random.uniform(0, 8);
  double fontScale=random.uniform(0, 100)*0.05+0.1; // [0.1 ,5.1]

  int thickness=8;
  // 得到hello 这几个字的大小
  Size textSize=cv::getTextSize("hello",fontFace,  fontScale,thickness, 0);
  std::cout << textSize << std::endl;
  // 这一行字 的左下角坐标
  Point bottom_left= Point((width-textSize.width)/2,(height-textSize.height));
  cv::putText(m, str,bottom_left,  fontFace,  fontScale, Scalar(255,255,0),thickness);

  cv::namedWindow("win");
  cv::imshow("win",m);
  cv::waitKey(0);
  return 0;
}
