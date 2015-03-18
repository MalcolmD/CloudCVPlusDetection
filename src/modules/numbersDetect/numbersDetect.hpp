#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


namespace cloudcv
{
	static cv::CascadeClassifier numbers_cascade;

	static std::vector<cv::Rect> detectAndDisplay(cv::Mat frame);

	static bool ProcessImage(cv::Mat image, cv::Rect& result);
}