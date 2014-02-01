//  -*- coding:utf-8-dos -*-
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
  int nimages=1;
  // int channels=0;



  int dims=1;
  int histSize=256;
  float range[]={0,256};
  const float *ranges = {range};
  bool uniform=true;
  bool accumulate=false;
  // b
  calcHist(&b_g_r_mats[0],  nimages,  0, Mat(),  b,  dims,  &histSize, &ranges,  uniform,  accumulate);
    // g
  calcHist(&b_g_r_mats[1],  nimages,  0, Mat(),  g,  dims,  &histSize, &ranges,  uniform,  accumulate);
    // r
  calcHist(&b_g_r_mats[2],  nimages,  0, Mat(),  r,  dims,  &histSize, &ranges,  uniform,  accumulate);


  // draw the histograms for b g r

  int bin_w=cvRound((double)(512/400));
  Mat histImage(512,400,CV_8UC3,Scalar(0,0,0));
  // normalize the result to [0,histImage.rows]
  normalize(b, b, 0, histImage.rows, NORM_MINMAX, -1,Mat());
  normalize(g, g, 0, histImage.rows, NORM_MINMAX, -1,Mat());
  normalize(r, r, 0, histImage.rows, NORM_MINMAX, -1,Mat());

  // draw for each channels
  for (int i = 0; i < histSize; ++i){
    line(b, Point(bin_w*(i-1),400-cvRound(b.at<float>(i-1))), Point(bin_w*(i),400-cvRound(b.at<float>(i))), Scalar(255,0,0));
    line(g, Point(bin_w*(i-1),400-cvRound(b.at<float>(i-1))), Point(bin_w*(i),400-cvRound(g.at<float>(i))), Scalar(0,255,0));
    line(r, Point(bin_w*(i-1),400-cvRound(b.at<float>(i-1))), Point(bin_w*(i),400-cvRound(r.at<float>(i))), Scalar(0,0,255));
  }

  namedWindow("histImage",WINDOW_NORMAL);
  imshow("histImage",histImage);

  waitKey(0);
  return 0;
}
