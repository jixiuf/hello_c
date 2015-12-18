//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
// 两种典型的 Morphological Transformation 形态的, 形态学的
// Eroding 侵蚀  and Dilating膨胀
// dilating ,白纸上一个小黑点 ，经膨胀后的效果是 小黑点的例会变大
// Eroding 应该是与膨胀的效果相反的

//
//1. erode
//2. dilate
// 其它的几种变换
//3.  open
//     open( src, element) = dilate( erode( src, element ) )
//     Useful for removing small objects (it is assumed that the objects are bright on a dark foreground)
//     原理就是 先缩小 后放大， 如果是小东西，缩小后更小， 更放大也不会有原来那么大
//4. close
//    close( src, element ) = erode( dilate( src, element ) )
//    Useful to remove small holes (dark regions).
//5. morph_{grad}( src, element ) = dilate( src, element ) - erode( src, element )
//   finding the outline of an object
// 6. tophat( src, element ) = src - open( src, element )

// 7. blackhat( src, element ) = close( src, element ) - src
// It is the difference between the closing and its input image



using namespace std;
using namespace cv;
Mat src, target;
int erosion_ele=0;
int erosion_size=0;

int max_eles=2;
int max_kernel_size=15;

int dilation_ele=0;
int dilation_size=0;

void erosion(int ,void*);
void dilation(int,void*);

const char* dilation_winname="win_dilate";
const char* erosion_winname="win_erosion";
int main(int argc, char *argv[])
{

  src=imread("in_color.png");
  if(src.empty()){
    exit(-1);
  }
  namedWindow(dilation_winname,WINDOW_NORMAL);
  namedWindow(erosion_winname,WINDOW_NORMAL);
  // cvMoveWindow(erosion_winname, src.cols, 0 );

  /// Create Erosion Trackbar
  createTrackbar( "rect_cross_ellipse", erosion_winname,
                  &erosion_ele, max_eles,
                  erosion );

  createTrackbar( "Kernel size:\n 2n +1", erosion_winname,
                  &erosion_size, max_kernel_size,
                  erosion );

  /// Create Dilation Trackbar
  createTrackbar("rect_cross_ellipse", dilation_winname,
                  &dilation_ele, max_eles,
                  dilation );

  createTrackbar( "Kernel size:\n 2n +1", dilation_winname,
                  &dilation_size, max_kernel_size,
                  dilation );

  erosion(0,0);
  dilation(0,0);
  waitKey(0);
  return 0;

}
// 两个未有到的参数是因为createTrackbar 接口要求
void erosion(int ,void*){
  int erosion_type;
  if (erosion_ele==0){
    erosion_type=MORPH_RECT;    // morph 形态
  }else if (erosion_ele==1){
    erosion_type=MORPH_CROSS;
  }else{
    erosion_type=MORPH_ERODE;
  }
  Mat ele =getStructuringElement(erosion_type,
                                 Size(2*erosion_size+1,2*erosion_size+1),
                                 Point(erosion_size,erosion_size));
  // 应该是用ele 所表示这段区域的像素值来计算出一个值
  erode(src,target,ele);
  imshow(erosion_winname,target);
}

// 两个未有到的参数是因为createTrackbar 接口要求
void dilation(int ,void*){
  int dilation_type;
  if (dilation_ele==0){
    dilation_type=MORPH_RECT;    // morph 形态
  }else if (dilation_ele==1){
    dilation_type=MORPH_CROSS;
  }else{
    dilation_type=MORPH_ERODE;
  }
  Mat ele =getStructuringElement(dilation_type,
                                 Size(2*dilation_size+1,2*dilation_size+1),
                                 Point(dilation_size,dilation_size));
  dilate(src,target,ele);
  imshow(dilation_winname,target);
}
