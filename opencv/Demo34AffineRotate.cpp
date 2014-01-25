//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/warp_affine/warp_affine.html#warp-affine
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst(src.size(),src.type());


  Mat rotateMat(2,3,CV_32FC1);
  Point2f center (src.cols/2,src.rows/2);
  double angle =-50.0;          // 旋转角度
  double scale=0.5;             // 一个因数， 我调整这个值，  转换后图片的可视大小有所调整
  rotateMat=getRotationMatrix2D(center, angle, scale);
  warpAffine(src, dst, rotateMat, dst.size());


  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  waitKey(0);
  return 0;
}
