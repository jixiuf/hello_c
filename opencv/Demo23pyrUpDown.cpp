//  -*- coding:utf-8-dos -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
// 放大缩小图片的像素值，

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{

  Mat src,dst,tmp;
  src=imread("in_color.png");
  if(src.empty()){
    exit(-1);
  }

  tmp=src;
  dst=tmp;
  namedWindow("press_d_or_u",WINDOW_NORMAL);
  imshow("press_d_or_u",dst);
  while(true){
    int c;
    c=waitKey(10);
    if(c=='d'){
      pyrDown(tmp,dst);
      imshow("press_d_or_u",dst);
      tmp=dst;
    }else if(c=='u'){
      pyrUp(tmp,dst);
      imshow("press_d_or_u",dst);
      tmp=dst;
    }else if(c==-1){
      // 没等到任何按键
    }else{
      break;
    }

  }
  return 0;

}
