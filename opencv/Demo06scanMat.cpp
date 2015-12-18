//  -*- coding:utf-8-unix -*-
// http://docs.opencv.org/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html#howtoscanimagesopencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
// 图片的色值替换， 遍历 Mat 的几种方法

Mat& scanMagAndReduce(Mat& input,const uchar* table){
  //  // accept only char type matrices
  // 保接触uchar 来表示的颜色值， 即<256
  // rgb颜色用3个数来表示 ，每个数可以选择uchar ushort ,或float等 ，这里
  // 只处理uchar类型的
  std::cout << "input.depth()=" <<input.depth()<< std::endl;
  CV_Assert(input.depth()!=sizeof(uchar));
  int channels=input.channels(); // 返回 channels, rgb是3,即用3个数表示一种颜色  ，灰色的则为1
  int rows=input.rows;           // Mat有多少行
  int cols=input.cols*channels;  // Mat列数*channels ,
  // Mat 可以理解成一个row*col 的矩阵，每个点上的元素记录着它的颜色， 对灰色图片
  // 来说 ，用一个数就可表示，用彩色rgb则需要3个数来表示,
  // 而这些 可以理解成 都存在一个一维数组里，
  // 所以 数组元素的个数是 rolws*cols*channels
  if(input.isContinuous()){     // 是否是连续的 ，行与行之前是否有gap
    // http://docs.opencv.org/modules/core/doc/basic_structures.html#mat-iscontinuous
    // 似乎 如果连续 ，只用一行就可以表示
    cols=rows*cols;
    rows=1;
  }
  uchar* p;
  for (int i = 0; i < rows; ++i) {
    p=input.ptr(i);
    for (int j = 0; j < cols; ++j){
      p[j]= table[p[j]];        // 用divide后的值取代原值
    }
  }
  return input;
}
// 更安全的遍历方式
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
  // accept only char type matrices
  CV_Assert(I.depth() != sizeof(uchar));

  const int channels = I.channels();
  switch(channels)
    {
    case 1:
      {
        MatIterator_<uchar> it, end;
        for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
          *it = table[*it];
        break;
      }
    case 3:
      {
        // Vec3b应该是3 byte
        MatIterator_<Vec3b> it, end;
        for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
          {
            (*it)[0] = table[(*it)[0]];
            (*it)[1] = table[(*it)[1]];
            (*it)[2] = table[(*it)[2]];
          }
      }
    }

  return I;
}

void method1(Mat& originMat,const uchar* table){
  Mat modified= scanMagAndReduce(originMat,table);
  cv::namedWindow("modified_mothed1");
  cv::imshow("modified_mothed1", modified);
}

void method2(Mat& originMat,const uchar* table){
  Mat modified= ScanImageAndReduceIterator(originMat,table);
  cv::namedWindow("modified_mothed2");
  cv::imshow("modified_mothed2", modified);
}
void method3(Mat& originMat,const uchar* table){
  Mat lookUpTable(1, 256, CV_8U);
  uchar* p = lookUpTable.data;
  for( int i = 0; i < 256; ++i)
    p[i] = table[i];
  Mat modified;
  // opencv提供的LUT ,查表替换
  LUT(originMat, lookUpTable, modified);
  cv::namedWindow("modified_mothed3");
  cv::imshow("modified_mothed3", modified);
}

int main( int argc, char** argv )
{
  int divideWith=10;
  // 从文件读一个img ,
  Mat originMat  = cv::imread("in_color.png",CV_LOAD_IMAGE_COLOR);
  if(! originMat.data )                              // Check for invalid input
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  cv::namedWindow("origin");
  cv::imshow("origin", originMat);

  // 处理方式是这样的， 没有必要 的rgb色值都精确的用确定的值表示 ，比如， 0~10，
  // 都用0来表示 ，11~20 都用10来表示， 对人眼来说 区别并不大
  uchar table[256];
  for (int i = 0; i < 256; ++i){
    table[i]=(uchar)  (divideWith* i/divideWith);
  }
  //效果都一样， 只是速度可能不同
  method1(originMat,table);
  method2(originMat,table);
  method3(originMat,table);
  waitKey(0);
  return 0;
}
