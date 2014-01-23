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

  Mat src = imread("in_color.png");
  Mat gray;
  cvtColor(src, gray, CV_RGB2GRAY);

  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat detected_edges;
  //先对图片进行 模糊化处理 ，去除一些干扰信息
  // First, we apply a GaussianBlur to our image to reduce the noise ( kernel size = 3 )
  GaussianBlur(gray, detected_edges, Size(3,3), 0);

  int lowerthreshold=30;        // 可以试着取1~100间的数
  // 我的理解是 检测到的边界 会用非0值，非边界则为0值，这样一副图中就可以正确区分别是边界哪是非边界
  Canny(detected_edges, detected_edges, lowerthreshold, lowerthreshold*3);

  Mat dst;
  dst=Mat::zeros(src.size(),src.type());

  // copyTo copy the src image onto dst. However, it will only copy the pixels
  // in the locations where they have non-zero values. Since the output of the
  // Canny detector is the edge contours on a black background, the resulting
  // dst will be black in all the area but the detected edges.
  // 把src 中与边界detected_edges重合的区域copy 到dst中
  src.copyTo(dst,detected_edges);
  // detected_edges.copyTo(dst);
  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  // 检测出的边界
  namedWindow("detected_edges",WINDOW_NORMAL); //
  imshow("detected_edges",detected_edges);

  waitKey(0);

  return 0;
}
