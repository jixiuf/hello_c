//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// 画 点线 圆 等图形
using namespace cv;
using namespace std;

void drawLine(Mat &m, Point start,Point end){
  int thickness = 2;            // 此参数可省略 ，默认是2
  int lineType=8;               // 此参数可省略 ，默认是8
  // cv::line(m, start, end, Scalar(100,100,0));
  cv::line(m, start, end, Scalar(100,100,0),thickness,lineType);

}
void drawEllipse(Mat &m,Point center,double angle){
  // 椭圆,angle ,是角度 ，0~360
  cv::ellipse(m, center, Size(100,50), angle, 0, 360, Scalar(255,0,0));
}
void fillCircle(Mat &m ,Point center ,int radius){
  cv::circle(m, center, radius, Scalar(0,0,255)); // red
}
void drawPolygon(Mat &m ){
  Point ps[1][4];
  ps[0][0]=Point(10,10);
  ps[0][1]=Point(100,100);
  ps[0][2]=Point(300,80);
  ps[0][3]=Point(110,120);
  const Point* ppt[1] = { ps[0] };
  int npt[]={4};
  fillPoly(m, ppt, npt, 1, Scalar(0,255,0) );
}
void drawRect(Mat &m){
  rectangle(m,
            Point( 30, 30 ),
            Point( 50,50),
            Scalar( 255, 0, 0 ),
            -1,
            8 );
}
int main( int argc, char** argv )
{
  int rows=400;
  int cols=400;
  // 8byte unsigned ,3channel
  Mat m1=Mat::zeros(rows, cols, CV_8UC3) ;

  drawLine(m1,Point(0,100),Point(100,300));

  drawEllipse(m1,Point(200,200),0);
  drawEllipse(m1,Point(200,200),45);

  fillCircle(m1, Point(200,200), 30);
  drawPolygon(m1);
  drawRect(m1);
  cv::namedWindow("win");
  cv::imshow("win",m1);
  cv::waitKey(0);
  return 0;
}
