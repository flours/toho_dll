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
	if (_cnt == 0 && _flag == 2) {//���̏u�Ԏ��񂾂�
		_x = Define::CENTER_X;//���W�Z�b�g
		_y = Define::IN_H + 30;
		_mutekicnt++;//���G��Ԃ�
		_life--;
	}
	if (_flag == 2) {//����ŕ��㒆�Ȃ�
		unsigned int push = Dllinput::input_check(Dllinput::left) + Dllinput::input_check(Dllinput::right)
			+ Dllinput::input_check(Dllinput::up) + Dllinput::input_check(Dllinput::down);
		_y -= 1.5;//�L��������ɏグ��
		//�P�b�ȏォ�A�L������������x��ɂ��āA���������ꂽ��
		if (_cnt > 60 || (_y < Define::IN_H - 10 && push)) {
			_cnt = 0;
			_flag = 0;//�L�����X�e�[�^�X�����ɖ߂�
		}
	}
	if (_mutekicnt > 0) {//���G�J�E���g��0����Ȃ����
		_mutekicnt++;
		if (_mutekicnt > 120)//�Q�b�ȏソ������
			_mutekicnt = 0;//�߂�
	}

	_cnt++;//�L�����N�^�J�E���g�A�b�v
	_img_id = (_cnt % 24) / 6;//���݂̉摜����
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
	if (moveX && moveY) { //�΂߈ړ�
		moveX /= (float)sqrt(2.0);
		moveY /= (float)sqrt(2.0);
	}
	if (Dllinput::input_check(Dllinput::slow) > 0) {//�ᑬ�ړ�
		moveX /= 3;
		moveY /= 3;
	}
	if (moveX + _x < Define::IN_X) {//���g��荶�Ȃ�
		_x = (float)Define::IN_X;   //���g�Ŏ~�߂�
	}
	else if (moveX + _x > Define::IN_X + Define::IN_W) {//�E�g���E�Ȃ�
		_x = (float)(Define::IN_X + Define::IN_W);      //�E�g�Ŏ~�߂�
	}
	else {//�g���Ȃ�
		_x += moveX;//���ʂɈړ�
	}
	if (moveY + _y < Define::IN_Y) {   //��g����Ȃ�
		_y = (float)Define::IN_Y;      //��g�Ŏ~�߂�
	}
	else if (moveY + _y > Define::IN_Y + Define::IN_H) {    //���g��艺�Ȃ�
		_y = (float)(Define::IN_Y + Define::IN_H);          //���g�Ŏ~�߂�
	}
	else {//�g���Ȃ�
		_y += moveY;//���ʂɈړ�
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

	//���@�ƓG�V���b�g�������������ǂ����𔻒肷��
	int j;
	for (int n = 0; n < Shot::SHOT_BULLET_MAX;n++)
	{
		if (bullet[n].cnt > 0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
			double x = bullet[n].x - getX();//�G�Ǝ��@�V���b�g�Ƃ̋���
			double y = bullet[n].y - getY();
			//�G�V���b�g�Ǝ��@�̓����蔻��̍��v�͈�
			double r = BulletInfo::bullet_ranges[bullet[n].knd] + CRANGE;

			//���Ԃ��v�Z����K�v�������
			if (bullet[n].spd > r) {
				//�P�t���[���O�ɂ����ʒu���i�[����
				double pre_x = bullet[n].x + cos(bullet[n].angle + Define::PI)*bullet[n].spd;
				double pre_y = bullet[n].y + sin(bullet[n].angle + Define::PI)*bullet[n].spd;
				double px, py;
				for (j = 0; j < bullet[n].spd / r; j++) {//�i�񂾕��������蔻�蕪���[�v
					px = pre_x - getX();
					py = pre_y - getY();
					if (px*px + py * py < r*r)
						hit(bullet, n);
					pre_x += cos(bullet[n].angle)*r;
					pre_y += sin(bullet[n].angle)*r;
				}
			}
			else if (x*x + y * y < r*r)//�����蔻����Ȃ�
				hit(bullet, n);
		}
	}
}

void Player::hit(bullet_t* bullet,int n) {
	bullet[n].flag = 0;//�e���I�t
						/*��炢�{�������������ɒǉ�*/
	if (_flag == 0 && _mutekicnt == 0) {//�X�e�[�^�X���ʏ�ŁA���G����Ȃ�������
		_flag = 2;    //1:��炢�{����t���@2:����ŕ����オ�蒆
		_cnt = 0;
	}
}

int Player::getreward() {
	int reward = 0;
	if (_cnt == 0 && _flag == 2) {//���̏u�Ԏ��񂾂�
		reward = -1;
	}
	return reward;
}

int Player::getdone() {
	return _life == 0 ? 1 : 0;
}