#include "SmallEnemy.h"
#include "Define.h"
#include "Image.h"
#include "Display.h"

SmallEnemy::SmallEnemy(float x, float y, std::shared_ptr<Player> player) : AbstractEnemy(x, y, player)
{
	_movePatternID = 3;
	_shotPatternID = 0;
	_hp = 1;
}

void SmallEnemy::draw() const
{
	cv::Mat _image = Image::getIns()->idToMat(Image::getIns()->getEnemySmall()[0]);
	_image = Display::affine_image(_image, 3 * _counter, 1.0);
	Display::draw_image(_image, _x, _y);

	_image = Image::getIns()->idToMat(Image::getIns()->getEnemySmall()[1]);
	_image = Display::affine_image(_image, 3 * (_counter+60), 1.0);
	Display::draw_image(_image, _x, _y);
	_shot.draw((AbstractEnemy*)this);

}

void SmallEnemy::setSize()
{
	cv::Mat _image = Image::getIns()->idToMat(Image::getIns()->getEnemySmall()[0]);
	_width = _image.cols;
	_height = _image.rows;
}
