//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
//1. erode
//2. dilate
// 以上两种操作见Demo21ErodingDilating.cpp
// 其它的几种形态变换
//3.  open
//     open( src, element) = dilate( erode( src, element ) )
//     Useful for removing small objects (it is assumed that the objects are bright on a dark foreground)
//     原理就是 先缩小 后放大， 如果是小东西，缩小后更小， 再次放大后也不会有原来那么大
//4. close
//    close( src, element ) = erode( dilate( src, element ) )
//    Useful to remove small holes (dark regions).
//5. morph_{grad}( src, element ) = dilate( src, element ) - erode( src, element )
//   finding the outline of an object 显出物体的轮廓
//6. tophat( src, element ) = src - open( src, element )
//    It is the difference between an input image and its opening.

//7. blackhat( src, element ) = close( src, element ) - src
//    It is the difference between the closing and its input image


    // Opening: MORPH_OPEN : 2
    // Closing: MORPH_CLOSE: 3
    // Gradient: MORPH_GRADIENT: 4
    // Top Hat: MORPH_TOPHAT: 5
    // Black Hat: MORPH_BLACKHAT: 6


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

  const char* winname="win";
  Mat src=imread("in_color.png");
  if(src.empty()){
    exit(-1);
  }
  namedWindow(winname,WINDOW_NORMAL);

  int size=13;       // 控制取样的范围
  // 用某个点附近一一个形状进一定的算法得到的值作为此点的新值
  int shape=MORPH_ELLIPSE;         // MORPH_RECT ,MORPH_CROSS MORPH_ELLIPSE
  Mat dst;
  // Returns a structuring element of the specified size and shape for morphological operations.
  Mat kernelParam= getStructuringElement(shape, Size(2*size+1,2*size+1),Point(size,size));
  // 可以进行的操作
  // int operator=MORPH_OPEN;//,MORPH_CLOSE,MORPH_GRADIENT,MORPH_TOPHAT,MORPH_DILATE,MORPH_BLACKHAT
  cv::morphologyEx(src, dst,MORPH_CLOSE, kernelParam);

  imshow(winname,dst);
  waitKey(0);
  return 0;

}
