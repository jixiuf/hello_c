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

Mat src ;
Mat template_mat;
Mat result;
char* win_src="src";
char* win_result="result";

int match_method;
int max_Trackbar=5;

void MatchingMethod(int ,void*);

int main(int argc, char *argv[]){

  src = imread("in_color.png");
  template_mat=imread("in_color_template.png");
  namedWindow(win_src,WINDOW_NORMAL);
  namedWindow(win_result,WINDOW_NORMAL);

  char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  createTrackbar( trackbar_label, win_src, &match_method, max_Trackbar, MatchingMethod );
  MatchingMethod( 0, 0 );

  waitKey(0);
  return 0;
}
void MatchingMethod(int ,void*){
  Mat img_disp;
  src.copyTo(img_disp);
  int result_cols=src.cols-template_mat.cols+1;
  int result_rows=src.rows-template_mat.rows+1;
  result.create(result_cols, result_rows, CV_32FC1);
  matchTemplate(src, template_mat,  result, match_method);

  double minVal,maxVal;
  Point minLoc,maxLoc;
  Point matchLoc;
  minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_disp, matchLoc, Point( matchLoc.x + template_mat.cols , matchLoc.y + template_mat.rows ),
             Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + template_mat.cols , matchLoc.y + template_mat.rows ),
             Scalar::all(0), 2, 8, 0 );

  imshow( win_src, img_disp );
  imshow(win_result, result );


}
