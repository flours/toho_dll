#include "Player.h"
#include "Dllinput.h"
#include "Display.h"
#include<iostream>
#include<cmath>
#include<opencv2/opencv.hpp>
#include "Image.h"
#include "Define.h"
#include "Shot.h"
#include "BulletInfo.h"
#include "Dllinput.h"

const static float SPEED = 9;


Player::Player() : 
_x((float)Define::CENTER_X),
_y((float)Define::CENTER_Y),
_shot(this),
_life(3),
_flag(0),
_cnt(0),
_mutekicnt(0)
{
}
	
bool Player::update()
{
	move();
	calc();
	_shot.shot();
	return true;
}

void Player::draw() const
{
	_shot.draw();
	if (_mutekicnt%2==0) {
		cv::Mat _image = Image::getIns()->idToMat(Image::getIns()->getPlayer());
		Display::draw_image(_image, _x, _y);
	}
}


void Player::calc() {
	if (_cnt == 0 && _flag == 2) {//今の瞬間死んだら
		_x = Define::CENTER_X;//座標セット
		_y = Define::IN_H + 30;
		_mutekicnt++;//無敵状態へ
		_life--;
	}
	if (_flag == 2) {//死んで浮上中なら
		unsigned int push = Dllinput::input_check(Dllinput::left) + Dllinput::input_check(Dllinput::right)
			+ Dllinput::input_check(Dllinput::up) + Dllinput::input_check(Dllinput::down);
		_y -= 1.5;//キャラを上に上げる
		//１秒以上か、キャラがある程度上にいて、何かおされたら
		if (_cnt > 60 || (_y < Define::IN_H - 10 && push)) {
			_cnt = 0;
			_flag = 0;//キャラステータスを元に戻す
		}
	}
	if (_mutekicnt > 0) {//無敵カウントが0じゃなければ
		_mutekicnt++;
		if (_mutekicnt > 120)//２秒以上たったら
			_mutekicnt = 0;//戻す
	}

	_cnt++;//キャラクタカウントアップ
	_img_id = (_cnt % 24) / 6;//現在の画像決定
}


void Player::move()
{
	float moveX = 0, moveY = 0;
	if (Dllinput::input_check(Dllinput::left) > 0) {
		moveX -= SPEED;
	}
	if (Dllinput::input_check(Dllinput::right) > 0) {
		moveX += SPEED;
	}
	if (Dllinput::input_check(Dllinput::down) > 0) {
		moveY += SPEED;
	}
	if (Dllinput::input_check(Dllinput::up) > 0) {
		moveY -= SPEED;
	}
	if (moveX && moveY) { //斜め移動
		moveX /= (float)sqrt(2.0);
		moveY /= (float)sqrt(2.0);
	}
	if (Dllinput::input_check(Dllinput::slow) > 0) {//低速移動
		moveX /= 3;
		moveY /= 3;
	}
	if (moveX + _x < Define::IN_X) {//左枠より左なら
		_x = (float)Define::IN_X;   //左枠で止める
	}
	else if (moveX + _x > Define::IN_X + Define::IN_W) {//右枠より右なら
		_x = (float)(Define::IN_X + Define::IN_W);      //右枠で止める
	}
	else {//枠内なら
		_x += moveX;//普通に移動
	}
	if (moveY + _y < Define::IN_Y) {   //上枠より上なら
		_y = (float)Define::IN_Y;      //上枠で止める
	}
	else if (moveY + _y > Define::IN_Y + Define::IN_H) {    //下枠より下なら
		_y = (float)(Define::IN_Y + Define::IN_H);          //下枠で止める
	}
	else {//枠内なら
		_y += moveY;//普通に移動
	}
}

float Player::getX() {
	return _x;

}


float Player::getY() {
	return _y;
}


double CRANGE = 2.0;

void Player::hit_judge(bullet_t* bullet) {

	//自機と敵ショットが当たったかどうかを判定する
	int j;
	for (int n = 0; n < Shot::SHOT_BULLET_MAX;n++)
	{
		if (bullet[n].cnt > 0) {//ショットの軌道が１度でも計算されていたら
			double x = bullet[n].x - getX();//敵と自機ショットとの距離
			double y = bullet[n].y - getY();
			//敵ショットと自機の当たり判定の合計範囲
			double r = BulletInfo::bullet_ranges[bullet[n].knd] + CRANGE;

			//中間を計算する必要があれば
			if (bullet[n].spd > r) {
				//１フレーム前にいた位置を格納する
				double pre_x = bullet[n].x + cos(bullet[n].angle + Define::PI)*bullet[n].spd;
				double pre_y = bullet[n].y + sin(bullet[n].angle + Define::PI)*bullet[n].spd;
				double px, py;
				for (j = 0; j < bullet[n].spd / r; j++) {//進んだ分÷当たり判定分ループ
					px = pre_x - getX();
					py = pre_y - getY();
					if (px*px + py * py < r*r)
						hit(bullet, n);
					pre_x += cos(bullet[n].angle)*r;
					pre_y += sin(bullet[n].angle)*r;
				}
			}
			else if (x*x + y * y < r*r)//当たり判定内なら
				hit(bullet, n);
		}
	}
}

void Player::hit(bullet_t* bullet,int n) {
	bullet[n].flag = 0;//弾をオフ
						/*喰らいボム処理をここに追加*/
	if (_flag == 0 && _mutekicnt == 0) {//ステータスが通常で、無敵じゃなかったら
		_flag = 2;    //1:喰らいボム受付中　2:死んで浮き上がり中
		_cnt = 0;
	}
}

int Player::getreward() {
	int reward = 0;
	if (_cnt == 0 && _flag == 2) {//今の瞬間死んだら
		reward = -1;
	}
	return reward;
}

int Player::getdone() {
	return _life == 0 ? 1 : 0;
}