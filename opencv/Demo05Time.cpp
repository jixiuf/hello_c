//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// opencv 计时
//  getTickCount(); // 返回从启动 到现在 的时钟tick
// frq=getTickFrequency() ,1秒的时间频率
// (tick1-tick2)/frq 经过的时间
int main( int argc, char** argv ) {
  double t = (double) getTickCount(); // 返回从启动 到现在 的时钟tick
  std::cout << "do sth" << std::endl;
  double t2 = (double) getTickCount();

  std::cout << (t2-t)/getTickFrequency() << std::endl;
}

