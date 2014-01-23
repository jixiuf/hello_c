//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst(src.size(),src.type());
  Mat mapx(src.size(),CV_32FC1 );
  Mat mapy(src.size(),CV_32FC1);

  for (int i = 0; i < src.rows; ++i){
    for (int j = 0; j < src.cols; ++j){
      mapx.at<float>(i,j)=src.cols-j; // x轴方向左右对换 ，
      mapy.at<float>(i,j)=i;
    }
  }

  remap(src, dst, mapx, mapy, CV_INTER_LINEAR);

  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  waitKey(0);
  return 0;
}
