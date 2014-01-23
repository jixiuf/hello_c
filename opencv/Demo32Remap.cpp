//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// remap 主要实现， 用图片中的某个位置的点来代替当前点， 达到图像反转，缩小等目的
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst(src.size(),src.type());
  // 我把这里改成src.type() 下面的mapx.at<float>改成mapx.at<int> 报错。
  // 这里用CV_32FC1  channel 为1 ， 普通rgb 是3，这里的mapx mapy 里面存的并不是像素值
  // 而是一个一维的坐标
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
