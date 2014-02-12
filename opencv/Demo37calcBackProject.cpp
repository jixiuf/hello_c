//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>
using namespace std;
using namespace cv;


// Back Projection is a way of recording how well the pixels of a given image
// fit the distribution of pixels in a histogram model.

// To make it simpler: For Back Projection, you calculate the histogram model of
// a feature and then use it to find this feature in an image.

// Application example: If you have a histogram of flesh color (say, a
// Hue-Saturation histogram ), then you can use it to find flesh color areas
// in an image:

// 比如 检测某张图片上  是否 有人皮肤的颜色


Mat src ,hsv,hue;
int bins=12;

void fun(int ,void*);

int main(int argc, char *argv[]){

  src = imread("in_hand_1.jpg");
  cvtColor(src, hsv, CV_BGR2HSV);


 // we will use only the Hue value for our 1-D histogram (check out the fancier
 // code in the links above if you want to use the more standard H-S histogram,
 // which yields better results):
  hue.create(hsv.size(), hsv.depth());
  int ch[]={0,0};
  // as you see, we use the function
  // http://docs.opencv.org/modules/core/doc/operations_on_arrays.html?highlight=mixchannels#mixchannelsmixChannels
  // to get only the channel 0 (Hue) from the hsv image. It gets the following
  // parameters:

  // &hsv: The source array from which the channels will be copied
  // 1: The number of source arrays
  // &hue: The destination array of the copied channels
  // 1: The number of destination arrays
  // ch[] = {0,0}: The array of index pairs indicating how the channels are
  // copied. In this case, the Hue(0) channel of &hsv is being copied to the 0
  // channel of &hue (1-channel)

  // 1: Number of index pairs
  mixChannels(&hsv, 1, &hue, 1, ch, 1);

  char* win_image="src";
  namedWindow(win_image,WINDOW_NORMAL);
  createTrackbar("Hue bins", win_image, &bins, 180,fun);
  fun(0,0);
  imshow(win_image, src);

  waitKey(0);
  return 0;
}
void fun(int ,void*){
  MatND hist;

  int histSize=MAX(bins,2);
  float hue_ranges[]={0,180};
  const float * ranges={hue_ranges};
  calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
  normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

  MatND backproj;
  calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

  // draw the backproj
  namedWindow("backproj",WINDOW_NORMAL);
  imshow( "backproj", backproj );

  int w=400,h=400;
  int bin_w=cvRound((double)w/histSize);
  Mat histImg=Mat::zeros(w,h, CV_8UC3);
  for (int i = 0; i < bins; ++i){
    rectangle(histImg, Point(i*bin_w,h), Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)), Scalar(0,0,255), -1);
  }
  namedWindow("Histogram",WINDOW_NORMAL);
  imshow( "Histogram", histImg );
}
