//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// calcHist
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  vector<Mat> b_g_r_mats;       // 把rgb 图片的Mat 分成3 份，分别存b g r 相应信息
  split(src, b_g_r_mats);

  Mat b, g ,r ;                 // output

  // The number of source arrays (in this case we are using 1. We can enter here also a list of arrays )
  int nimages=1;
  // int channels=0;

  //  The histogram dimensionality.
  int dims=1;

  // The number of bins per each used dimension
  int histSize=256;             // num of bins

  // The range of values to be measured per each dimension
  float range[]={0,256};        // 前闭后开的区间， 所以是256 而非255 ,实际可取 0 ～255 之间的值
  const float *ranges = {range};

  // We want our bins to have the same size (uniform) and to clear the histograms in the beginning, so:
  bool uniform=true;
  bool accumulate=false;

  // 参数0 The channel (dim) to be measured. In this case it is just the intensity (each array is single-channel)
  // so we just write 0.
  // b
  calcHist(&b_g_r_mats[0],  nimages,  0, Mat(),  b,  dims,  &histSize, &ranges,  uniform,  accumulate);
    // g
  calcHist(&b_g_r_mats[1],  nimages,  0, Mat(),  g,  dims,  &histSize, &ranges,  uniform,  accumulate);
    // r
  calcHist(&b_g_r_mats[2],  nimages,  0, Mat(),  r,  dims,  &histSize, &ranges,  uniform,  accumulate);

  // Create an image to display the histograms:
  // 以下只是对calcHist的图形化展示
  // draw the histograms for b g r

  int hist_w=512;
  int hist_h=400;
  int bin_w=cvRound((double)(hist_w/histSize));
  Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));

  // normalize the result to [0,histImage.rows]
  // Notice that before drawing, we first normalize the histogram so its values fall in the range indicated by the parameters entered:
  // -1: Implies that the output normalized array will be the same type as the input
  normalize(b, b, 0, histImage.rows, NORM_MINMAX, -1,Mat());
  normalize(g, g, 0, histImage.rows, NORM_MINMAX, -1,Mat());
  normalize(r, r, 0, histImage.rows, NORM_MINMAX, -1,Mat());

  // // draw for each channels
  for (int i = 0; i < histSize; ++i){
    line(histImage, Point(bin_w*(i-1),hist_h-cvRound(b.at<float>(i-1))), Point(bin_w*(i),hist_h-cvRound(b.at<float>(i))), Scalar(255,0,0));
    line(histImage, Point(bin_w*(i-1),hist_h-cvRound(b.at<float>(i-1))), Point(bin_w*(i),hist_h-cvRound(g.at<float>(i))), Scalar(0,255,0));
    line(histImage, Point(bin_w*(i-1),hist_h-cvRound(b.at<float>(i-1))), Point(bin_w*(i),hist_h-cvRound(r.at<float>(i))), Scalar(0,0,255));
  }

  namedWindow("histImage",WINDOW_NORMAL);
  imshow("histImage",histImage);

  waitKey(0);
  return 0;
}
