//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/laplace_operator/laplace_operator.html#laplace-operator
// 拉普拉斯算子
// 一次求导 可以变斜率变化最大的点变成最高点，
// 二次求导后这个最高点就变成了0  ，
// 可以通过二次求导后 的0点 寻找边界
// 但是 二次求导后是0 的点 并不一定是斜率变化最大的点， 还有其他一些干扰点
// 但是经 拉普拉斯算子处理之后 ，则可以
// 感觉 处理后的图片 效果很暗，
using namespace std;
using namespace cv;
int main(int argc, char *argv[]){

  Mat gray = imread("in_color.png",CV_LOAD_IMAGE_GRAYSCALE);
  // Mat gray;
  Mat dst,abs_dst;
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",gray);

  //先对图片进行 模糊化处理 ，去除一些干扰信息
  // First, we apply a GaussianBlur to our image to reduce the noise ( kernel size = 3 )
  GaussianBlur(gray, gray, Size(3,3), 0);

  // cvtColor(src, gray, CV_RGB2GRAY);
  // Mat grad_dst;
  // ddepth: The depth of the output image. We set it to CV_16S to avoid overflow.
  int ddepth=CV_16S;
  int kernel_size=3;

  Laplacian( gray, dst, ddepth, kernel_size);
  convertScaleAbs( dst, abs_dst );

  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",abs_dst);
  waitKey(0);

  return 0;
}
