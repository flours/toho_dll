#pragma once
#include "Singleton.h"
#include <vector>
#include "opencv2/opencv.hpp"

class Size {
public:
	Size() : w(0), h(0) {}
	Size(int w, int h) : w(w), h(h) {}
	int getWidth()  const { return w; }
	int getHeight() const { return h; }
private:
	int w, h;
};

class ImageBullet final : public Singleton<ImageBullet> {

public:
	enum eBulletType {
		eSmall,	//0
		eBarrier,	//1
		eSparkSmall,   //2
		eKome,		//3
		eUmaibo,	//4
		eSparkBig,	//5
		eKodama,	//6
		eYosei,	//7
		eRing,		//8
		eAme,		//9
		eTama,		//10
		eOdama,	//11
		eLaser,	//12
		eOfuda,	//13
		eStar,		//14
		eRain,		//15
		eRainbow,	//16
		eTypeNum,
	};

	enum eBulletColor {
		eBlue,
		ePurple,
		ePink,
		eOrenge,
		eYellow,
		eGreen,
		eLime,
		eAqua,
		eColorNum,
	};

	const static float RANGE[];
	const static float SORT_Z[];

	ImageBullet();
	cv::Mat getimg(unsigned int type, unsigned int color);
	int get(unsigned int type, unsigned int color) const;

private:
	std::vector<int*> _list;
	std::vector<Size*> _sizeList;
	std::vector<cv::Mat> _images;

	void load() {}
	void myLoadDivGraph(const char* fname);

	const Size* getSize(unsigned int type) const;
};