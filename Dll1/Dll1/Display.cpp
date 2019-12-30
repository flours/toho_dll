#include<opencv2/opencv.hpp>
#include "Define.h"
#include "Display.h"
#include<iostream>
#include <stdio.h>

cv::Mat Display::main_image(Define::WIN_H, Define::WIN_W, CV_8UC3,cv::Scalar(255));
int Display::_reward = 0;
int Display::_done = 0;
int Display::_life = 0;
int Display::reset_flag = 0;

void Display::image_reset() {
	Display::main_image = cv::Mat(Define::WIN_H, Define::WIN_W, CV_8UC3, cv::Scalar(0,0,0));
}

cv::Mat Display::affine_image(cv::Mat src,double deg,double scale) {
	cv::Point2f center = cv::Point2f(
		static_cast<float>(src.cols / 2),
		static_cast<float>(src.rows / 2));


	// アフィン変換行列
	cv::Mat affine;
	cv::getRotationMatrix2D(center, deg, scale).copyTo(affine);
	cv::Mat dst;
	cv::warpAffine(src, dst, affine, src.size(), cv::INTER_CUBIC);
	return dst;
}



void Display::draw_image(cv::Mat image,int x,int y) {
	int w = image.cols;
	int h = image.rows;
	int orig_x = x;
	int orig_y = y;

	if ((int)orig_x + image.cols / 2 <= 0)return;
	if ((int)orig_y + image.rows / 2 <= 0)return;
	if ((int)orig_x - image.cols / 2 <= 0) { w = image.cols + ((int)orig_x - image.cols / 2); x = 0; }
	else x -= w/2;
	if ((int)orig_y - image.rows / 2 <= 0) { h = image.rows + ((int)orig_y - image.rows / 2); y = 0; }
	else y -= h/2;
	if ((int)orig_x - image.cols / 2 >= Define::OUT_W)return;
	if ((int)orig_y - image.rows / 2 >= Define::OUT_H)return;
	if ((int)orig_x + image.cols / 2 >= Define::OUT_W) { w = Define::OUT_W - ((int)orig_x - image.cols / 2);	x = Define::OUT_W - w; }

	if ((int)orig_y + image.rows / 2 >= Define::OUT_H) { h = Define::OUT_H - ((int)orig_y - image.rows / 2);	y = Define::OUT_H - h; }

	cv::Mat roi = Display::main_image(cv::Rect(x, y, w, h));

	std::vector<cv::Mat> planes;
	if ((int)orig_x - image.cols / 2 < 0)x = -((int)orig_x - image.cols / 2);
	else x = 0;
	if ((int)orig_y - image.rows / 2 < 0)y = -((int)orig_y - image.rows / 2);
	else y = 0;
//	printf("a");
	image = image(cv::Rect(x, y, w, h));

	cv::Mat newimg;
	cv::split(image, planes);

	cv::Mat mask;
	std::vector<cv::Mat> mask_v;

	mask_v.push_back(planes[3]);
	mask_v.push_back(planes[3]);
	mask_v.push_back(planes[3]);

	cv::merge(mask_v, mask);

	cv::Mat img2;
	std::vector<cv::Mat> img;
	img.push_back(planes[0]);
	img.push_back(planes[1]);
	img.push_back(planes[2]);

	cv::merge(img, img2);


	cv::bitwise_and(mask, img2, newimg);
	cv::bitwise_not(mask, mask);
	cv::Mat img3;
	cv::bitwise_and(mask, roi, img3);
	img3 = img3 + newimg;

	img3.copyTo(roi);
//	printf("b");

}
void Display::set_reward(int reward) {
	_reward = reward;
}
void Display::set_done(int done) {
	_done = done;
}
void Display::set_life(int life) {
	_life = life;
}

void Display::getdatas(int* reward, int* done,int *life) {
	*reward = _reward;
	*done = _done;
	*life = _life;
}

void Display::reset() {
	reset_flag = 1;
}