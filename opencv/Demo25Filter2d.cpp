//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

// 自定义 linear filter
// 通过一个kernal 矩阵 对image的每个像素点执行一定变换，
// filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor, double delta, int borderType)
//ddepth 为负数则 结果与src depth 相同
// kernel 用于转换的矩阵
// anchor Point(-1,-1 ),则以矩阵的中心点作为anchor 点， 我的理解是 当把某个像素点
//        应用操作时， 把此点与anchor 点位置进行重合后应用Kernel的变换，变换的结果作为此点的结果
// delta 是一个偏移 对上述计算的结果都加上此值
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

  int ddepth=-1;
  Point anchor(-1,-1);
  int delta =0;
  RNG rng;
  int kernel_size=rng.uniform(3,8); // 3 ~8 随机一个数
  // 我试了一下，CV_32F 改成 CV_8UC3 似乎没法运行
  Mat kernel = Mat::ones(Size(kernel_size,kernel_size), CV_32F)/(float)(kernel_size* kernel_size);

  filter2D(src,dst,ddepth,kernel,anchor,delta);

  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);
  waitKey(0);
  return 0;

}
