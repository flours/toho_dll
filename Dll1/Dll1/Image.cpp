#include <iostream>
#include "Image.h"
#include <opencv2/opencv.hpp>

Image::Image()
{
	_player = myLoadGraph("dat/image/player/body/seishi0.png");
	_cShot = myLoadGraph("dat/image/player/bullet01.png");
	myLoadDivGraph("dat/image/enemy/normal.png", 9, 3, 3, 27, 27, _enemyNormal);
	myLoadDivGraph("dat/image/enemy/big.png", 9, 3, 3, 80, 60, _enemyBig);
	myLoadDivGraph("dat/image/enemy/small.png", 2, 2, 1, 16, 16, _enemySmall);
}

/*!
@brief 今までロードした画像を解放する
*/
void Image::release()
{
	_images.clear();
}

/*!
@brief get_____で手に入れたidをMatに変換する
*/
cv::Mat Image::idToMat(int id) {
	return _images.at(id);
}


/*!
@brief プレイヤーの画像を取得する
*/
int Image::getPlayer() const
{
	return _player;
}

int Image::getcShot() const
{
	return _cShot;
}

/*!
@brief _imagesにpushbackして_images内の画像idを渡す
*/
int Image::myLoadGraph(const char *fileName)
{
	cv::Mat ret = cv::imread(fileName,cv::ImreadModes::IMREAD_UNCHANGED);
	_images.push_back(ret.clone());
	return _images.size()-1;
}

/*!
@brief LoadDivGraphをして、かつそのハンドルをメンバ変数に追加する
*/
int Image::myLoadDivGraph(const char *fileName, int n, int xn, int yn, int w, int h,int* buf)
{
	int ret;
	cv::Mat img_orig = cv::imread(fileName,cv::ImreadModes::IMREAD_UNCHANGED);
//	int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	if (yn == 1)yn = 2;
	ret = _images.size();

	for (int i = 0; i < n; i++) {
		buf[i] = ret + i;
		cv::Mat img = img_orig(cv::Rect(i%xn*w,i/yn*h,w,h));
		_images.push_back(img.clone());
	}
	return ret;
}