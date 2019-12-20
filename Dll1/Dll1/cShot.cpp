#include "cShot.h"
#include "Display.h"
#include "Image.h"
#include "Define.h"
#include "Player.h"
#include "Dllinput.h"

const int cShot::cshot0pos_x[4] = {-10,10,-30,30};
const int cShot::cshot0pos_y[4] = {-30,-30,-10,-10};
const int cShot::cshot0num[2] = {2,4};

cShot::cShot(Player*  player) {
	_player = player;
	memset(cshot, 0, sizeof(cshot));
}


void cShot::draw() const{
	for (int i = 0; i < CSHOT_MAX; i++) {
		if (cshot[i].flag > 0) {
			Display::draw_image(Image::getIns()->idToMat(Image::getIns()->getcShot()), cshot[i].x, cshot[i].y);
		}
	}
}


void cShot::shot() {
	calc_cshot();//�V���b�g�̋O���v�Z
	enter_shot();//�V���b�g�o�^
}

void cShot::shot0() {
	int k;
	for (int i = 0; i < cshot0num[power < 200 ? 0 : 1]; i++) {
		if ((k = search_cshot()) != -1) {
			cshot[k].flag = 1;
			cshot[k].cnt = 0;
			cshot[k].angle = -Define::PI / 2;
			cshot[k].spd = 20;
			cshot[k].x = _player->getX() + cshot0pos_x[i];
			cshot[k].y = _player->getY() + cshot0pos_y[i];
			cshot[k].power = 23;
			cshot[k].knd = 0;
		}
	}
}
void cShot::shot1() {
	int k;
	for (int i = 0; i < cshot0num[power < 200 ? 0 : 1]; i++) {
		if ((k = search_cshot()) != -1) {
			cshot[k].flag = 1;
			cshot[k].cnt = 0;
			cshot[k].angle = -Define::PI / 2;
			cshot[k].spd = 20;
			cshot[k].x = _player->getX() + cshot0pos_x[i] / 3;//�ᑬ���Ȃ�ʒu�𒆐S����
			cshot[k].y = _player->getY() + cshot0pos_y[i] / 2;
			cshot[k].power = 23;
			cshot[k].knd = 0;
		}
	}
}

void cShot::calc_cshot() {
	for (int i = 0; i < CSHOT_MAX; i++) {
		if (cshot[i].flag == 1) {
			int dranx = cshot[i].spd + 11 / 2, drany = cshot[i].spd + 55 / 2;
			cshot[i].x += cos(cshot[i].angle)*cshot[i].spd;
			cshot[i].y += sin(cshot[i].angle)*cshot[i].spd;
			cshot[i].cnt++;
			if (cshot[i].x<-dranx || cshot[i].x>Define::OUT_W + dranx ||
				cshot[i].y<-drany || cshot[i].y>Define::OUT_H + drany)//��ʂ���O�ꂽ��
				cshot[i].flag = 0;
		}
	}
}
void cShot::enter_shot() {
	//�V���b�g�{�^����������Ă�����
	if ( Dllinput::input_check(Dllinput::shot)> 0) {
		shot_cnt++;
		if (shot_cnt % 3 == 0) {//3�J�E���g��1��
			if (Dllinput::input_check(Dllinput::slow) > 0)//�ᑬ�ړ����Ȃ�
				shot0();
			else
				shot1();
		}
	}
	else
		shot_cnt = 0;
}
int cShot::search_cshot() {
	for (int i = 0; i < CSHOT_MAX; i++) {
		if (cshot[i].flag == 0)
			return i;
	}
	return -1;
}


//Player* _player;
//int flag, power, cnt, knd;
//double x, y, angle, spd;

