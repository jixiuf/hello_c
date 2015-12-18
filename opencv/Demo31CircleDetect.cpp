//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// 检测一副图中的圆
int main(int argc, char *argv[]){

  Mat src = imread("in_circle.jpg");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat gray;
  cvtColor(src, gray, CV_BGR2GRAY);


  Mat dst;
  src.copyTo(dst);
  GaussianBlur(gray, gray, Size(9,9), 2,2);

  namedWindow("blur",WINDOW_NORMAL);
  imshow("blur",gray);

  vector<Vec3f> circles;

  // gray: Input image (grayscale)
  // circles: A vector that stores sets of 3 values: x_{c}, y_{c}, r for each detected circle.
  // CV_HOUGH_GRADIENT: Define the detection method. Currently this is the only one available in OpenCV
  // dp = 1: The inverse ratio of resolution
  // min_dist = gray.rows/8: Minimum distance between detected centers
  // param_1 = 200: Upper threshold for the internal Canny edge detector
  // param_2 = 100*: Threshold for center detection.
  // min_radius = 0: Minimum radio to be detected. If unknown, put zero as default.
  // max_radius = 0: Maximum radius to be detected. If unknown, put zero as default
  HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, dst.rows/50, 200, 100, 0, 0 );
  // HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows()/8);
  for (size_t i = 0; i < circles.size(); ++i){
    Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
    int radius=cvRound(circles[i][2]);
    circle(dst, center, 3, Scalar(0,0,255)); //
    circle(dst, center, radius, Scalar(255,0,0));
  }



  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);


  waitKey(0);

  return 0;
}
