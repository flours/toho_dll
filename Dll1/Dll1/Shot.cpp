#include "Shot.h"
#include "AbstractEnemy.h"
#include "Macro.h"
#include "ImageBullet.h"
#include "Player.h"
#include "Define.h"
#include "ImageBullet.h"
#include "Display.h"
#include<iostream>

double Shot::shotatan2(AbstractEnemy *enemy) {//���@�ƓG�Ƃ̐����p�x
	return atan2(_player->getY() - enemy->getY(), _player->getX() - enemy->getX());
}

int Shot::shot_search() {
	int i;
	for (i = 0; i < Shot::SHOT_BULLET_MAX; i++) {
		if (bullet[i].flag == 0) {
			return i;
		}
	}
	return -1;
}

Shot::Shot(std::shared_ptr<Player> player) {
	_player = player;
	memset(bullet, 0, sizeof(bullet));
	setFunction();
	flag = knd = cnt = num = 0;
}

bool Shot::update(AbstractEnemy *enemy) {
	shot(enemy);
	Bullet_calc();
	cnt++;
	return bullet_inside();
}

bool Shot::bullet_inside() {
	for (int i = 0; i < Shot::SHOT_BULLET_MAX; i++)
		if (bullet[i].flag > 0)
			return true;
	return false;
}


//�e�̋O���v�Z
void Shot::Bullet_calc() {
	for (int i = 0; i < Shot::SHOT_BULLET_MAX; i++) {//n�Ԗڂ̒e���f�[�^�̒e���v�Z
		if(bullet[i].flag > 0) {//���̒e���o�^����Ă�����
			bullet[i].x += cos(bullet[i].angle)*bullet[i].spd;
			bullet[i].y += sin(bullet[i].angle)*bullet[i].spd;
			bullet[i].cnt++;
			if (bullet[i].x<-50 || bullet[i].x>Define::OUT_W + 50 ||
				bullet[i].y<-50 || bullet[i].y>Define::OUT_H + 50) {//��ʂ���O�ꂽ��
				if (bullet[i].till < bullet[i].cnt)//�Œ�����Ȃ����Ԃ�蒷�����
					bullet[i].flag = 0;//����
			}
		}
	}
}

void Shot::shot(AbstractEnemy *enemy) {
	const unsigned int id = enemy->getShotPatternID();
	if (_shotPattern.size() <= id) {
		ERR("shotID���s���ł�");
	}
	(this->*_shotPattern[id])(enemy);  //id�ɉ������ړ��������s��
}

void Shot::draw(AbstractEnemy *enemy) const {
	for (int i = 0; i < SHOT_BULLET_MAX; i++) {//���̒e�������e�̍ő吔�����[�v
		if (bullet[i].flag != 0) {//�e�f�[�^���I���Ȃ�
			cv::Mat _image = ImageBullet::getIns()->getimg(bullet[i].knd,bullet[i].col);
			_image = Display::affine_image(_image, bullet[i].angle+180, 1.0);
			Display::draw_image(_image, bullet[i].x, bullet[i].y);
		}
	}
}

void Shot::setFunction() {
	_shotPattern.push_back(&Shot::shotPattern00);
}

void Shot::enter_shot(AbstractEnemy *enemy) {
}

void Shot::shotPattern00(AbstractEnemy *enemy) {
	int k;
	if (cnt == 50) {
		if (flag != 2 && (k = shot_search()) != -1) {
			bullet[k].knd = ImageBullet::eBulletType::eKodama;
			bullet[k].angle = shotatan2(enemy);
			bullet[k].flag = 1;
			bullet[k].x = enemy->getX();
			bullet[k].y = enemy->getY();
			bullet[k].col = ImageBullet::eBulletColor::eOrenge;
			bullet[k].cnt = 0;
			bullet[k].spd = 3;
		}
	}
}