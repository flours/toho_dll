#pragma once
#include<opencv2/opencv.hpp>

class Display {
private:
	static int _reward;
	static int _done;
	static int _life;

public:
	static int reset_flag;
	static cv::Mat main_image;
	static void image_reset();
	static void draw_image(cv::Mat img,int x,int y);
	static cv::Mat affine_image(cv::Mat src, double degree, double scale);
	static void getdatas(int* reward, int* done,int* life);
	static void set_reward(int reward);
	static void set_done(int done);
	static void set_life(int life);
	static void reset();
};

