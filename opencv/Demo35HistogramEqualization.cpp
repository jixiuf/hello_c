//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// 似乎  是跟对比度相关，  ,计算出 跟对比度相关的东西， 然后以直方图的方式显示出来，
// 似乎使关键物体的对比度相应增强，不重要物体的对比度减小
// 但是我下面的代码跟 教程上的显示效果完全不一致
// http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_equalization/histogram_equalization.html#histogram-equalization
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png",CV_LOAD_IMAGE_GRAYSCALE);
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst;
  equalizeHist(src, dst);



  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  waitKey(0);
  return 0;
}
