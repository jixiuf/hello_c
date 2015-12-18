//  -*- coding:utf-8-unix -*-
// Tracker10.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  cv::VideoCapture capWebcam(0);		// declare a VideoCapture object and associate to webcam, 0 => use 1st webcam

  if(capWebcam.isOpened() == false) {			// check if VideoCapture object was associated to webcam successfully
    std::cout << "error: capWebcam not accessed successfully\n\n";	// if not, print error message to std out
    return(1);														// and exit program
  }

  cv::Mat matOriginal;		// "Matrix object, used for images in OpenCV2, this will be the input image from the webcam
  cv::Mat matProcessed;		// "Matrix object, used for images in OpenCV2, this will be the processed image

  std::vector<cv::Vec3f> vecCircles;				// 3 element vector of floats, this will be the pass by reference output of HoughCircles()
  std::vector<cv::Vec3f>::iterator itrCircles;	// iterator for the circles vector

  cv::namedWindow("Original");			// original image from webcam
  cv::namedWindow("Processed");			// processed image we will use for detecting circles

  char charCheckForEscKey = 0;

  while(charCheckForEscKey != 27) {		// for each frame (until the Esc key is pressed) . . .
    if(capWebcam.read(matOriginal) == NULL) {	// get next frame from webcam, check if returned NULL
      std::cout << "error: frame not read from webcam\n\n";	// if returned NULL, print error message to std out
      break;													// and jump out of while loop
    }

    // call inRange to take original image and turn into processed image
    cv::inRange(matOriginal,				// funcion input
                cv::Scalar(0,0,175),		// min filtering value (if greater than or equal to this) (in BGR format)
                cv::Scalar(100,100,256),	// max filtering value (and if less than this) (in BGR format)
                matProcessed);				// function output

											// smooth the processed image, this will make it easier for the next function to identify circles
    cv::GaussianBlur(matProcessed,			// function input
                     matProcessed,			// function output
                     cv::Size(9,9),			// smoothing window width and height in pixels
                     1.5);					// sigma value, determines how much the image will be blurred

    // fill circles vector with all circles in processed image
    cv::HoughCircles(matProcessed,				// input image
                     vecCircles,				// function output (must be a standard template library vector
                     CV_HOUGH_GRADIENT,			// two-pass algorithm for detecting circles, this is the only choice available
                     2,							// size of image / this value = "accumulator resolution", i.e. accum res = size of image / 2
                     matProcessed.rows / 4,		// min distance in pixels between the centers of the detected circles
                     100,						// high threshold of Canny edge detector (called by cvHoughCircles)
                     50,						// low threshold of Canny edge detector (set at 1/2 previous value)
                     10,						// min circle radius (any circles with smaller radius will not be returned)
                     400);						// max circle radius (any circles with larger radius will not be returned)

    for(itrCircles = vecCircles.begin(); itrCircles != vecCircles.end(); itrCircles++) {

      std::cout << "ball position x = " << (*itrCircles)[0]				// x position of center point of circle
                << ", y = " << (*itrCircles)[1]				// y position of center point of circle
                << ", z = " << (*itrCircles)[2] << "\n";		// radius of circle

      // draw small green circle at center of detected object
      cv::circle(matOriginal,													// draw on original image
                 cv::Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]),		// center point of circle
                 3,															// radius of circle in pixels
                 cv::Scalar(0,255,0),											// draw pure green (remember, its BGR, not RGB)
                 CV_FILLED);													// thickness, fill in the circle

      // draw red circle around the detected object
      cv::circle(matOriginal,													// draw on original image
                 cv::Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]),		// center point of circle
                 (int)(*itrCircles)[2],										// radius of circle in pixels
                 cv::Scalar(0,0,255),											// draw pure red (remember, its BGR, not RGB)
                 3);															// thickness of circle in pixels
    }	// end for

    cv::imshow("Original", matOriginal);			// original image with detected ball overlay
    cv::imshow("Processed", matProcessed);			// image after processing

    charCheckForEscKey = cv::waitKey(10);			// delay (in ms) and get key press, if any
  }	// end while

  return(0);
}
