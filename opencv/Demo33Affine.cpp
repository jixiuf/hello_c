//  -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/warp_affine/warp_affine.html#warp-affine
// 仿射变换 跟前一个remap 有点类似 。
// 大概就是一些扭曲 旋转 之类的。
// 在图A中的三个点 。对应图B中另外三个点。然后其他所有点 这依照这个对应关系 计算其相应的位置
int main(int argc, char *argv[]){

  Mat src = imread("in_color.png");
  namedWindow("src",WINDOW_NORMAL);
  imshow("src",src);

  Mat dst(src.size(),src.type());

  Point2f srcTri[3];
  Point2f dstTri[3];
  Mat warpMat(2,3,CV_32FC1);

  srcTri[0]= Point2f(0,0);
  srcTri[1]= Point2f(src.cols,0);
  srcTri[2]= Point2f(0,src.rows);

  dstTri[0]=Point2f(src.cols*0.33,src.rows*0.33);
  dstTri[1]=Point2f(src.cols*0.66,src.rows*0.33);
  dstTri[2]=Point2f(src.cols*0.50,src.rows*0.86);
  warpMat=getAffineTransform(srcTri, dstTri); // 定义两组 三角形 之间的对应关系， 计算出一个2*3矩阵

  // 然后对整张图片应用上述转换关系
  warpAffine(src, dst, warpMat, dst.size());



  namedWindow("dst",WINDOW_NORMAL);
  imshow("dst",dst);

  waitKey(0);
  return 0;
}
