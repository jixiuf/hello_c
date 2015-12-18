//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// 检测一副图中的直线
int main(int argc, char *argv[]){

  Mat src = imread("in_room.jpg",CV_LOAD_IMAGE_GRAYSCALE);

  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst,color;
  GaussianBlur(src, dst, Size(3,3), 0);
  Canny(dst, dst, 50, 200);
  cvtColor(dst, color, CV_GRAY2BGR);

  float in_rho =1;              // he resolution of the parameter r in pixels. We use 1 pixel.
  float in_theta=CV_PI/180;     // 角度The resolution of the parameter \theta in radians. We use 1 degree (CV_PI/180)
  // 这个值越高， 符合条件的直线越少，threshold: The minimum number of intersections to “detect” a line
  float threading=200;
   // The minimum number of points that can form a line. Lines with less than this number of points are disregarded.
  double minLineLen=50;
  double maxLineGap=10;
  // maxLineGap: The maximum gap between two points to be considered in the same line.
  //dst : Output of the edge detector. It should be a grayscale image (although in fact it is a binary one)
  vector<Vec4i> lines;
  HoughLinesP(dst, lines, in_rho, in_theta, threading, minLineLen, maxLineGap);
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    line( color, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }


  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  namedWindow("color",WINDOW_NORMAL);
  imshow("color",color);

  waitKey(0);

  return 0;
}
