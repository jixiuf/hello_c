//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
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
