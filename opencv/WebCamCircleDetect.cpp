//  -*- coding:gbk -*-
// #include <iostream>
#include <opencv/cxcore.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <stdio.h>
#include <stdlib.h>
// using namespace std;
// ��Ҫʵ�� ������ͷǰ�ƶ�һ��Բ�����壬�˳��� �ܹ�׷�ٴ�����Ĺ켣
// ���� ʹ����opencv1 �ĺ�����
int main(int argc, char *argv[]){
  // ������Ҫ������ͷ������Ҳ���������С
  CvSize size640x480=cvSize(640,480);
  CvCapture *pCapture;
  IplImage *pImgOrig, *pImgProcessed;
  CvMemStorage *pMemStorage;
  CvSeq *pSeqCircles;
  float *pXYRadius;                // 0 1 2 ,x,y,radius
  int i;
  char CEsc;

  pCapture = cvCaptureFromCAM(0); // 0 use first webcam
  if(pCapture==NULL){
    printf ("error,CAM is NULL\n");
    getchar();                // print a char ,exit
    return -1;
  }

  cvNamedWindow("Origin", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("Processed", CV_WINDOW_AUTOSIZE);
  pImgProcessed=cvCreateImage(size640x480,
                              IPL_DEPTH_8U, //  // 8bit color  depth
                              1);             // one channel (graycolor) if this is a  color image ,use 3
  while(true){
    pImgOrig = cvQueryFrame(pCapture);//get frame from webcam
    if(pImgOrig==NULL){
      printf ("error frame null\n");
      getchar();                // print a char ,exit
      break;
    }
    cvInRangeS(pImgOrig,
               CV_RGB(175,0,0),   // min filter value, if color  is greater than or equal this
               CV_RGB(256,100,100), // max filter value ( if color is less than this)
               pImgProcessed);
    pMemStorage=cvCreateMemStorage(0); // alloc mem to pass into cvHoughCircles();
    // smooth the processed image ,this will make the next function easy to pick up the circle
    cvSmooth(pImgProcessed,            // input
             pImgProcessed             // output
             ,CV_GAUSSIAN,    //    // us gaussian filter (average nearly pixel,with closest pixel weightd more)
             9,9);             // smooth filter window width and height

    // fill pSeqCircles with all circle in processed image
    // �Ӵ������ͼƬ�� ���˳����е�Բ�� Ȼ����䵽 pSeqCircles
    pSeqCircles=cvHoughCircles(pImgProcessed, // input, , has to be grayscale (no color)
                               pMemStorage,    // provide this function with mem storage
                               CV_HOUGH_GRADIENT, // two-pass algorithm for detecting the circles ,��ͼƬ�м���ǲ���Բ���㷨��Ŀǰֻ֧����һ���㷨��
                               2,                 // size of image /2 = accumulator resolution, i.e. acc=res=size of image/2
                               pImgProcessed->height/4, // min distance in pixel between the centors of the detected circles
                               100,                     // hight threshold(����) of canny(��ȷ��) edeg  detector ,called by cvHoughCircles
                               50,                      // lower threshold of canny edeg detector
                               10, //min redius of circle
                               400 // max redius of circle
                               );
    for (i = 0; i < pSeqCircles->total; i++){ // ����ÿ����⵽��circle
      pXYRadius=(float*)cvGetSeqElem(pSeqCircles, i);
      printf ("x=%f,y=%f,r=%f\n",pXYRadius[0],pXYRadius[1],pXYRadius[2]); // x, y ,r
      // draw a small green circle �ڼ��ĵ�Բ �ڲ���һ��СԲ
      cvCircle(pImgOrig,
               cvPoint(pXYRadius[0],pXYRadius[1]), // x y  point
               3, //3 pixel,  or   pXYRadius[2],                       // r �뾶,
               CV_RGB(0,255,0),
               CV_FILLED      // ʵ��
               );

      cvCircle(pImgOrig,
               cvPoint(pXYRadius[0],pXYRadius[1]), // x y  point
               3, //3 pixel,  or   pXYRadius[2],                       // r �뾶,
               CV_RGB(0,255,0),
               CV_FILLED      // ʵ��
               );
    } // end for
    cvShowImage("Origin",pImgOrig);
    cvShowImage("Processed",pImgProcessed);
    cvReleaseMemStorage(&pMemStorage);
    CEsc=cvWaitKey(10);     // delay 10ms
    if(CEsc==27){           // exit esc,jump out of while
      break;
    }

  } // end while

  cvReleaseCapture(&pCapture);
  cvDestroyWindow("Origin");
  cvDestroyWindow("Processed");
  return 0;
}
