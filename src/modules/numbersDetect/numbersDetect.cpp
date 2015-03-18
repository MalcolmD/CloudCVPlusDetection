#include "numbersDetect.hpp"
#include <iostream>
#include <stdio.h>
#include <string>


namespace cloudcv
{


 

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

    //-- Convert image to grayscale
    cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect numbers
   numbers_cascade.detectMultiScale( frame_gray, number_sets, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

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
  bool ProcessImage(cv::Mat image, cv::Rect& result)
  {
   std::string numbers_cascade_name = "numbers_cascade.xml";
   std::vector<cv::Rect> results;


   //-- 1. Load the numbers cascade
   if( !numbers_cascade.load( numbers_cascade_name ) ){ printf("--(!)Error loading cascade\n"); return false; };

   //-- 3. Apply the classifier to the frame
   if(!image.empty())
    results = detectAndDisplay(image); 
   else
    printf(" --(!) No captured frame -- Break!"); 

   //-- Return the first detection obtained
   result = results[0];

   //-- Return that a detection was found
   return true;
  }


  
}