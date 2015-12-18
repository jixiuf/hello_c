//  -*- coding:utf-8-unix -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_COLOR);
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  // 截取某一范围内的图片
  Mat B(originMat,Rect(10,10,200,200));
  cv::namedWindow("rect",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("rect", B);


  // 截取某一范围内的图片
  // using row and column boundaries
  //  originMat(Range::all(),Range(1,30)); 取 originMat 的所有行，  [1-30) 列  包括1 不包括30
  // Range 应该是一个范围，  从一个点到另一个点 ， 两个这样的range就划定了一个矩形
  Mat C= originMat(Range::all(),Range(1,30));
  cv::namedWindow("range",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("range", C);


  //  originMat(Range(1,3),Range::all()); 取 originMat  [1-3) 行 包括1 不包括3 ，Range::all()所有列
  Mat D= originMat(Range(1,100),Range::all());
  cv::namedWindow("range2",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("range2", D);


  // The Scalar is four element short vector Scalar 这个类 是一个含4个元素的vector
  // Scalar::all(0) =[0, 0, 0, 0]
  // Scalar(0,0,255) =[0, 0, 255, 0]
  std::cout <<  Scalar(0,0,255) << std::endl; //

  // count Mat 只能找例子2维及以下的 ，3 维的 打印出来人眼看不出效果，很难打印
  // CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
  // 比如CV_8UC3  最后的3 表示 这是个三维的点, 决定了 取用Scalar所表示的4个元素中的几个
  //自己构造 matrix 2行 3 列 8字节的 3 维点阵
  Mat M(2,3, CV_8UC3, Scalar(0,0,255));
  cout << "M = " << endl << " " << M << endl << endl;
  // M =
  //  [0, 0, 255, 0, 0, 255, 0, 0, 255;
  //   0, 0, 255, 0, 0, 255, 0, 0, 255]

  Mat M2(2,3, CV_8UC4, Scalar(0,0,255,1));
  cout << "M2 = " << endl << " " << M2 << endl << endl;
  // M2 =
  //  [0, 0, 255, 1, 0, 0, 255, 1, 0, 0, 255, 1;
  //   0, 0, 255, 1, 0, 0, 255, 1, 0, 0, 255, 1]



  // CV_8UC3 means we use unsigned char types that are 8 bit long and each pixel
  // has three of these to form the three channels. This are predefined for up
  // to four channel numbers. The Scalar is four element short vector. Specify
  // this and you can initialize all matrix points with a custom value. If you
  // need more you can create the type with the upper macro, setting the channel
  // number in parenthesis as you can see below.

  int sz[3] = {2,2,2};
  Mat L(3,sz, CV_8UC(1), Scalar::all(0)); // 可以想像成 长宽高 各为2 的三维物体，各个点上的数值是 [0]
  // The upper example shows how to create a matrix with more than two dimensions.
  // Specify its dimension, then pass a pointer containing the size for each
  // dimension and the rest remains the same.
  // 第一个参数 表示 几维 ，
  // 第2个数组 表示 每一维的size
  //后面的两个参数 同上

  Mat G = Mat::eye(5, 5, CV_64F);
  cout << "G = " << endl << " " << G << endl << endl;
 // G=
 // [1, 0, 0, 0, 0;
 //  0, 1, 0, 0, 0;
 //  0, 0, 1, 0, 0;
 //  0, 0, 0, 1, 0;
 //  0, 0, 0, 0, 1]

  Mat O = Mat::ones(2, 2, CV_32F);
  cout << "O = " << endl << " " << O << endl << endl;
  // O =
  //  [1, 1;
  //   1, 1]

  Mat Z = Mat::zeros(3,3, CV_8UC1);
  cout << "Z = " << endl << " " << Z << endl << endl;
  // Z =
  //  [0, 0, 0;
  //   0, 0, 0;
  //   0, 0, 0]

  Point2f P(5, 1);
  cout << "Point (2D) = " << P << endl << endl;

  Point3f P3(5, 1,2);
  cout << "Point (3D) = " << P3 << endl << endl;

  vector<float> v;
  v.push_back( (float)CV_PI);   v.push_back(2);    v.push_back(3.01f);
  cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;

  // std::cout << D << std::endl;
  // Met 分为header和data 部分，
  // A(B) A=B , Mat B(originMat,Rect(10,10,400,400)), 等 只是header不同，  其data 指向同一个地方 ，通过引用计数来决定何时清空data内存
  // A=B.clone() ,or A=copeTo(B) ，则会 复制data部分
  cv::waitKey(0);
  return 0;
}
