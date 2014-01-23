//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

// copyMakeBorder
// 通过copy 某个区域(或0值等) 作为新图片的边界

int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  Mat dst;
  RNG rng;

  // the size of border
  int top=(int)0.09*src.rows;
  int bottom= (int)0.09*src.rows;
  int left=(int)0.09*src.cols;
  int right=(int)0.09*src.cols;

  // BORDER_CONSTANT 使用常量
  // BORDER_REFLECT 用某个区域替换

  // value: If borderType is BORDER_CONSTANT, this is the value used to fill the border pixels.
  Scalar value =Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
  int borderType=BORDER_REFLECT;
  copyMakeBorder(src, dst, top, bottom, left, right, borderType,value);

  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  namedWindow("win",WINDOW_NORMAL);
  imshow("win",dst);
  waitKey(0);

  return 0;
}
