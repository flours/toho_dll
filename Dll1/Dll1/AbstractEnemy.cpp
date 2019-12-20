#include "AbstractEnemy.h"
#include "Image.h"
#include "Define.h"
#include "Display.h"
#include "Player.h"

AbstractEnemy::AbstractEnemy(float x, float y,std::shared_ptr<Player> player) : 
	_x(x),
	_y(y),
	_player(player),
	_shot(player),
	_speed(0),
	_angle(0),
	_counter(0),
	_width(0),
	_height(0) 
{
}

void AbstractEnemy::initialize()
{
	setSize();
}


bool AbstractEnemy::update()
{
	_mover.move(this);
	bool shot_inside=_shot.update(this);
	_counter++;
	return isInside() || shot_inside;
}

/*!
@brief 現在の位置が画面内か？
*/
bool AbstractEnemy::isInside() const
{
	if (_counter < 60) {//最初の1秒は判定しない
		return true;
	}
	if (_x < -_width / 2 || Define::OUT_W + _width / 2 < _x || _y < -_height / 2 || Define::OUT_H + _height / 2 < _y) {
		return false;
	}
	return true;
}



int AbstractEnemy::getSize() {
	return _width;
}

//敵の当たり判定範囲
int enemy_range[4] = { 16,30,16,50 };
//自機ショットの当たり判定範囲
int cshot_range[1] = { 6, };


bool AbstractEnemy::hit_judge(cshot_t cshot[cShot::CSHOT_MAX]) {
	int j;
	for (int i = 0; i < cShot::CSHOT_MAX; i++) {
		if (cshot[i].cnt > 0) {//ショットの軌道が１度でも計算されていたら
			double x = cshot[i].x - getX();//敵と自機ショットとの距離
			double y = cshot[i].y - getY();

			//敵の当たり判定と自機ショットの当たり判定の合計範囲
			double r = cshot_range[cshot[i].knd] + getSize();

			//中間を計算する必要があれば
			if (cshot[i].spd > r) {
				//１フレーム前にいた位置を格納する
				double pre_x = cshot[i].x + cos(cshot[i].angle + Define::PI)*cshot[i].spd;
				double pre_y = cshot[i].y + sin(cshot[i].angle + Define::PI)*cshot[i].spd;
				double px, py;
				for (j = 0; j < cshot[i].spd / r; j++) {//進んだ分÷当たり判定分ループ
					px = pre_x - getX();
					py = pre_y - getY();
					if (px*px + py * py < r*r) {
						cshot[i].flag = 0;//その自機ショットを消す
						_hp -= cshot[i].power;//弾の持つパワー分HPを減らす
						break;
					}
					pre_x += cos(cshot[i].angle)*r;
					pre_y += sin(cshot[i].angle)*r;
				}
			}
			else if (x*x + y * y < r*r)//当たり判定内なら
			{
				cshot[i].flag = 0;//その自機ショットを消す
				_hp -= cshot[i].power;//弾の持つパワー分HPを減らす
			}
		}
	}
	if (_hp <= 0)return false;
	return true;
}


