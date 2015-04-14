#include "objectsDetect.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


namespace cloudcv
{
  
  cv::CascadeClassifier objects_cascade;

  /* Function that does the actual detection.
  * ---Parameters---
  * (frame) - image we want to analyze
  *
  * ---Return value---
  * Vector containing all detections captured. */
  std::vector<cv::Rect> detectAndDisplay( cv::Mat frame )
  {
    
    std::vector<cv::Rect> number_sets;
    cv::Mat frame_gray;

    cv::setNumThreads(0);

    //-- Convert image to grayscale
    cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

   //-- Detect objects
   std::cout << "before call" << std::endl;
   objects_cascade.detectMultiScale( frame_gray, number_sets, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE);
   std::cout << "after call" << std::endl;


   //-- Format rectangle data to be acceptable input
   //-- The rectangles will thereafter store member variables:
   //-- int x1, int x2, int y1, int y2 instead of int x, int y, int width, int height
   for(std::vector<cv::Rect>::iterator it = number_sets.begin(); it < number_sets.end(); ++it)
    {
      it->width += it->x;
      it->height += it->y;
    }
   
   //-- Return vector of detections
   return number_sets;
  }


  /* Function called from NAN
  * ---Parameters---
  * (Image) - image we want to analyze
  * (result) - Returned by reference, this is one detection capture
  *
  * ---Return value---
  * Returns a bool value whether a detection was captured or not */
  bool ProcessImage(cv::Mat image,  std::vector<cv::Rect>& result)
  {
   cv::String objects_cascade_name = "haarcascade_frontalface_alt.xml";
   
   //std::vector<cv::Rect> results;

   
   //-- 1. Load the objects cascade
   if( !objects_cascade.load( objects_cascade_name ) )
   {
    printf("--(!)Error loading cascade\n"); 
    return false; 
   }

   //-- 2. Apply the classifier to the frame
   if(!image.empty())
    result = detectAndDisplay(image); 
   else
    printf(" --(!) No captured frame -- Break!"); 


   //-- Return the first detection obtained
   // result = results[0];

   //-- Return that a detection was found
   return true;
  }

}