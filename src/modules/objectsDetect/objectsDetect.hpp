#pragma once

#include <opencv2/opencv.hpp>

namespace cloudcv
{

	std::vector<cv::Rect> detectAndDisplay(cv::Mat frame);
	bool ProcessImage(cv::Mat image, std::vector<cv::Rect>& result);
}