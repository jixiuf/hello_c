//  -*- coding:utf-8-unix -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
// 对比度  亮度调整
//g(x) = alpha* f(x) + beta
// alpha beta 通常称为 gain(增益) , bias(偏差) 字面翻译
// a控制 对比度contrast  b控制亮度brightness
//g(i,j) = alpha * f(i,j) + beta ,可以认为f(i,j) 为位置(i,j)的像素值

// 下面的代码 演示了如何通过遍历每一个像素，  来改变 其亮度 对比度
// opencv 提供Mat:convertTo,来实现下面复杂的过程
// image.convertTo(new_image, -1, alpha, beta);

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  // 从文件读一个img ,
  // 当以CV_LOAD_IMAGE_GRAYSCALE 方式读取的时候， channels()==1
  Mat originMat  = cv::imread("in_color.png");
  // Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_GRAYSCALE);
  std::cout << "depth=" <<originMat.depth() << std::endl;
  std::cout << "channels=" <<originMat.channels()<< std::endl;
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  // CV_Assert(originMat.depth() != sizeof(uchar));

  cv::namedWindow("origin1",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("origin1", originMat);

  Mat newMat=Mat::zeros(originMat.size(), originMat.type());
  double alpha=1.5 ;                // 1.0~3.0
  int beta=50;                     // 0~100
  std::cout << originMat.channels() << std::endl;
  for (int i = 0; i < originMat.rows; ++i){
    for (int j = 0; j < originMat.cols; ++j){
      if(originMat.channels()==3){ // 彩色图
        Vec3b cell=originMat.at<Vec3b>(i,j);
        for (int k = 0; k < 3; ++k){
          // saturate_cast与强制转换不同的是， 如果超过了上下限， 则返回上下限,而不是简单的截断
          newMat.at<Vec3b>(i,j)[k] = saturate_cast<uchar>( cell[k]*alpha+beta);
        }
      }else if(originMat.channels()==1){ // 灰色图
        uchar cell=originMat.at<uchar>(i,j);
        newMat.at<uchar>(i,j)= saturate_cast<uchar>( cell*alpha+beta);
      }
    }
  }


  cv::namedWindow("changed",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("changed",newMat);


  Mat changed_by_convertto;
  int rtype=-1;
  // rtype – desired output matrix type or, rather, the depth since the number
  // of channels are the same as the input has; if rtype is negative, the output
  // matrix will have the same type as the input.
  originMat.convertTo(changed_by_convertto, rtype, alpha, beta); // alpha 对比度， beta亮度

  cv::namedWindow("changed_by_convertto",WINDOW_NORMAL);
  // 在这个窗口中 显示上面加载的img
  cv::imshow("changed_by_convertto",changed_by_convertto);
  cv::waitKey(0);
  return 0;
}
