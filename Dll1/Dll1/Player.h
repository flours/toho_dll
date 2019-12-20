#pragma once

#include "Task.h"
#include<opencv2/opencv.hpp>
#include "cShot.h"
#include "Shot.h"

class Player : public Task
{
public:
	Player();
	virtual ~Player() = default;
	bool update() override;
	void draw() const override;
	float getX();
	float getY();
	cShot* getcShot() { return &_shot; }
	void hit_judge(bullet_t* bullet);

private:

	int _flag;
	int _mutekicnt;
	int _cnt;
	int _img_id;

	void hit(bullet_t* bullet, int n);
	void calc();

	void move();
	cShot _shot;
	float _x, _y;   //À•W
	cv::Mat _image;     //‰æ‘œƒnƒ“ƒhƒ‹
};