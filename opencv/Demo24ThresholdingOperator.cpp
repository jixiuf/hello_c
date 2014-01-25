//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
// Thresholding Operations 阀值 相关的操作
// 比如从一个图片中分离出某个物体(根据像素值的差别)
// threshold() 提供了5种类型的操作
// 1.Threshold Binary
//   dst(x,y) =  maxValue (if  src(x,y)>thresh)
//               0        (others)
// 2 Threshold Binary, Inverted
//   dst(x,y) =  0        (if  src(x,y)>thresh)
//               maxValue (others)
// 3 Truncate
//   dst(x,y) =  thresh         (if  src(x,y)>thresh)
//               src(x,y)       (others)
// 4 Threshold to Zero
//   dst(x,y) =  thresh         (if  src(x,y)>thresh)
//               0              (others)
// 5 Threshold to Zero, Inverted
//   dst(x,y) =  0              (if  src(x,y)>thresh)
//               src(x,y)       (others)

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{

  Mat src,dst;
  src=imread("in_color.png");
  if(src.empty()){
    exit(-1);
  }

  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  namedWindow("winname",WINDOW_NORMAL);
  int threshold_value = 100;    // 阀值,可以通过调整这个值 来观查 以什么值的时候 可以正确区分出我们想要的物体
  int maxval=255;
  // 类型 可取值 THRESH_BINARY THRESH_BINARY_INV,THRESH_TRUNC THRESH_TOZERO THRESH_TOZERO_INV
  int threshold_type=THRESH_BINARY; //
  threshold(src, dst, threshold_value, maxval, threshold_type);
  imshow("winname",dst);
  waitKey(0);
  return 0;

}
