//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// 边界检测Canny
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png",CV_LOAD_IMAGE_GRAYSCALE);
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  //先对图片进行 模糊化处理 ，去除一些干扰信息
  // First, we apply a GaussianBlur to our image to reduce the noise ( kernel size = 3 )
  GaussianBlur(src, src, Size(3,3), 0);

  Mat detected_edges;
  int lowerthreshold=30;        // 可以试着取1~100间的数
  Canny(src, detected_edges, lowerthreshold, lowerthreshold*3);

  Mat dst;
  dst=Mat::zeros(src.size(),src.type());

  // copyTo copy the src image onto dst. However, it will only copy the pixels
  // in the locations where they have non-zero values. Since the output of the
  // Canny detector is the edge contours on a black background, the resulting
  // dst will be black in all the area but the detected edges.
  src.copyTo(dst,detected_edges);
  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);
  waitKey(0);

  return 0;
}
