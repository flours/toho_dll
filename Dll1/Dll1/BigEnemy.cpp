#include "BigEnemy.h"
#include "Image.h"
#include "Define.h"
#include "Display.h"
#include "Player.h"

BigEnemy::BigEnemy(float x, float y,std::shared_ptr<Player> player) : AbstractEnemy(x, y,player)
{
	_movePatternID = 3;
	_shotPatternID = 0;
	_hp = 1;
}

void BigEnemy::draw() const
{
	const static int imgID[4] = { 0,1,2,1 };
	int add = 3;
	if (cos(_angle) > 0.1) {//‰EŒü‚«
		add = 6;
	}
	if (cos(_angle) < -0.1) {//¶Œü‚«
		add = 0;
	}
	int handle = Image::getIns()->getEnemyBig()[add + imgID[(_counter / 8) % 4]];
	cv::Mat _image = Image::getIns()->idToMat(handle);
	Display::draw_image(_image, _x, _y);

	_shot.draw((AbstractEnemy*)this);
}

void BigEnemy::setSize()
{
	cv::Mat _image = Image::getIns()->idToMat(Image::getIns()->getEnemyBig()[0]);
	_width = _image.cols;
	_height = _image.rows;
}