#pragma once

#include "Singleton.h"
#include <vector>
#include <opencv2/opencv.hpp>

class Image final : public Singleton<Image> {

public:
	Image();
	~Image() = default;
	void load() {}
	void release();

	int  getPlayer() const;
	const int* getEnemySmall() const { return _enemySmall; }
	const int* getEnemyNormal() const { return _enemyNormal; }
	const int* getEnemyBig() const { return _enemyBig; }
	int getcShot() const;

	cv::Mat idToMat(int id);

private:
	int myLoadGraph(const char*);
	int myLoadDivGraph(const char *fileName, int n, int xn, int yn, int w, int h,int* buf);

	std::vector<cv::Mat> _images;
	int _player;
	int _enemySmall[2];
	int _enemyNormal[9];
	int _enemyBig[9];
	int _cShot;
};
