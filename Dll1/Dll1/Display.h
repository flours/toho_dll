#pragma once
#include<opencv2/opencv.hpp>

class Display {
private:

public:
	static cv::Mat main_image;
	static void image_reset();
	static void draw_image(cv::Mat img,int x,int y);
	static cv::Mat affine_image(cv::Mat src, double degree, double scale);
};

