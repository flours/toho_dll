#include "ImageBullet.h"
#include "Macro.h"
#include "opencv2/opencv.hpp"
const float WEIGHT = 0.71f;//���̓����蔻��͈͂̒����l
//�����蔻�蔼�a
const float RANGE[] =
{
	 5.5f * WEIGHT,//Small
	 4.0f * WEIGHT,//Barrier
	 4.0f * WEIGHT,//SparkSmall
	 5.0f * WEIGHT,//Kome
	 4.5f * WEIGHT,//Umaibo
	 9.0f * WEIGHT,//SparkBig
	10.0f * WEIGHT,//Kodama	//����12.0f
	 6.5f * WEIGHT,//Yosei
	 9.0f * WEIGHT,//Ring
	11.0f * WEIGHT,//Ame
	19.5f * WEIGHT,//Tama	//����23.0f
	38.0f * WEIGHT,//Odama
	 2.8f * WEIGHT,//Laser
	10.0f * WEIGHT,//Ofuda
	 5.0f * WEIGHT,//Star
	 6.0f * WEIGHT,//Rain
	 9.0f * WEIGHT,//Rainbow
};
//Z�\�[�g
const int SORT_Z[] =
{
	 1,//Small
	 5,//Barrier
	 4,//SparkSmall
	 2,//Kome
	 7,//Umaibo
	 8,//SparkBig
	12,//Kodama
	10,//Yosei
	11,//Ofuda
	12,//Ring
	14,//Ame
	15,//Tama
	16,//Odama
	 3,//Laser
	 5,//Star
	 6,//Rain
	 9,//Rainbow
};

ImageBullet::ImageBullet()
{
	_sizeList.push_back(new Size(8, 8));//0
	_sizeList.push_back(new Size(14, 15));//1
	_sizeList.push_back(new Size(19, 19));//2
	_sizeList.push_back(new Size(9, 15));//3
	_sizeList.push_back(new Size(32, 32));//4
	_sizeList.push_back(new Size(38, 38));//5
	_sizeList.push_back(new Size(16, 16));//6
	_sizeList.push_back(new Size(27, 27));//7
	_sizeList.push_back(new Size(18, 18));//8
	_sizeList.push_back(new Size(15, 28));//9
	_sizeList.push_back(new Size(31, 31));//10
	_sizeList.push_back(new Size(54, 54));//11
	_sizeList.push_back(new Size(6, 120));//12
	_sizeList.push_back(new Size(14, 16));//13
	_sizeList.push_back(new Size(17, 17));//14
	_sizeList.push_back(new Size(10, 17));//15
	_sizeList.push_back(new Size(10, 10));//16
	myLoadDivGraph("dat/image/bullet/00.small.png");
	myLoadDivGraph("dat/image/bullet/01.barrier.png");
	myLoadDivGraph("dat/image/bullet/02.sparkSmall.png");
	myLoadDivGraph("dat/image/bullet/03.kome.png");
	myLoadDivGraph("dat/image/bullet/04.umaibo.png");
	myLoadDivGraph("dat/image/bullet/05.sparkBig.png");
	myLoadDivGraph("dat/image/bullet/06.kodama.png");
	myLoadDivGraph("dat/image/bullet/07.yosei.png");
	myLoadDivGraph("dat/image/bullet/08.ring.png");
	myLoadDivGraph("dat/image/bullet/09.ame.png");
	myLoadDivGraph("dat/image/bullet/10.tama.png");
	myLoadDivGraph("dat/image/bullet/11.odama.png");
	myLoadDivGraph("dat/image/bullet/12.laser.png");
	myLoadDivGraph("dat/image/bullet/13.ofuda.png");
	myLoadDivGraph("dat/image/bullet/14.star.png");
	myLoadDivGraph("dat/image/bullet/15.rain.png");
	myLoadDivGraph("dat/image/bullet/16.rainbow.png");
}

/*!
@brief �e�̉摜�����[�h����_list�Ɋi�[����
*/
void ImageBullet::myLoadDivGraph(const char* fname)
{
	int id = _list.size();
	Size* size = _sizeList[id];
	int *bullets = new int[eColorNum];
//	LoadDivGraph(fname, eColorNum, eColorNum, 1, size->getWidth(), size->getHeight(), bullets);
	int ret;
	int n = eColorNum;
	int xn = eColorNum;
	int w = size->getWidth();
	int h = size->getWidth();
	cv::Mat img_orig = cv::imread(fname, cv::ImreadModes::IMREAD_UNCHANGED);

	//	int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	ret = _images.size();

	for (int i = 0; i < n; i++) {
		bullets[i] = ret + i;
		cv::Mat img = img_orig(cv::Rect(i%xn*w, 0, w, h));
		_images.push_back(img.clone());
	}
	_list.push_back(bullets);
}

/*!
@brief type��ʂ�color�F�̒e�̉摜�n���h�����擾
*/
int ImageBullet::get(unsigned int type, unsigned int color) const
{
	if (eTypeNum <= type) {
		ERR("�e��type���s���ł�");
	}
	if (eColorNum <= color) {
		ERR("�e��color���s���ł�");
	}
	return _list[type][color];
}

cv::Mat ImageBullet::getimg(unsigned int type, unsigned int color) {
	if (eTypeNum <= type) {
		ERR("�e��type���s���ł�");
	}
	if (eColorNum <= color) {
		ERR("�e��color���s���ł�");
	}
	return _images.at(_list[type][color]);
}


/*!
@brief type��ʂ̉摜�T�C�Y��Ԃ�
*/
const Size* ImageBullet::getSize(unsigned int type) const
{
	if (_sizeList.size() <= type) {
		ERR("wh_t��getSize�̎w�肪�Ԉ���Ă��܂�");
	}
	return _sizeList[type];
}