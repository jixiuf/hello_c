//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/sobel_derivatives/sobel_derivatives.html#sobel-derivatives

using namespace std;
using namespace cv;
// 求导 操作， 主要用途 是找出某个物体的边界
// 通过求导 可以使渐变的过程 变得明显
// 通过计算两个像素之间的差别
// Sobel
int main(int argc, char *argv[]){

  Mat gray = imread("in_color.png",CV_LOAD_IMAGE_GRAYSCALE);
  // Mat gray;
  Mat dst;
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",gray);

  //先对图片进行 模糊化处理 ，去除一些干扰信息
  // First, we apply a GaussianBlur to our image to reduce the noise ( kernel size = 3 )
  GaussianBlur(gray, gray, Size(3,3), 0);

  // cvtColor(src, gray, CV_RGB2GRAY);

  Mat grad_x,grad_y;            // 斜率
  Mat abs_grad_x, abs_grad_y;
  // ddepth: The depth of the output image. We set it to CV_16S to avoid overflow.
  int ddepth=CV_16S;
  int kernel_size=3;

  // 计算x 斜率
  // Notice that to calculate the gradient in x direction we use: x_{order}= 1
  // and y_{order} = 0. We do analogously for the y direction.
  Sobel(gray, grad_x, ddepth, 1, 0,kernel_size);
  convertScaleAbs(grad_x, abs_grad_x);
  // 注意 计算 x  y斜率时 1 0,0 1 的区别
  Sobel(gray, grad_y, ddepth, 0, 1,kernel_size);
  // 当kernel size =3 时 ， 速度比Sobel 快， (下面Scharr的调用里没有传kernel_size
  // Scharr(gray, grad_y, ddepth, 0, 1);

  // We convert our partial results back to CV_8U:

  // // convertScaleAbs! scales array elements, computes absolute values and
  // converts the results to 8-bit unsigned integers:
  // dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
  convertScaleAbs(grad_y, abs_grad_y);

  // 将各自计算的x y  方向的 图片 进行合并
  // 各自比重0.5
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);
  waitKey(0);

  return 0;
}
