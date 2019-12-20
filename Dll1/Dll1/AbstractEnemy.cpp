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
@brief ���݂̈ʒu����ʓ����H
*/
bool AbstractEnemy::isInside() const
{
	if (_counter < 60) {//�ŏ���1�b�͔��肵�Ȃ�
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

//�G�̓����蔻��͈�
int enemy_range[4] = { 16,30,16,50 };
//���@�V���b�g�̓����蔻��͈�
int cshot_range[1] = { 6, };


bool AbstractEnemy::hit_judge(cshot_t cshot[cShot::CSHOT_MAX]) {
	int j;
	for (int i = 0; i < cShot::CSHOT_MAX; i++) {
		if (cshot[i].cnt > 0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
			double x = cshot[i].x - getX();//�G�Ǝ��@�V���b�g�Ƃ̋���
			double y = cshot[i].y - getY();

			//�G�̓����蔻��Ǝ��@�V���b�g�̓����蔻��̍��v�͈�
			double r = cshot_range[cshot[i].knd] + getSize();

			//���Ԃ��v�Z����K�v�������
			if (cshot[i].spd > r) {
				//�P�t���[���O�ɂ����ʒu���i�[����
				double pre_x = cshot[i].x + cos(cshot[i].angle + Define::PI)*cshot[i].spd;
				double pre_y = cshot[i].y + sin(cshot[i].angle + Define::PI)*cshot[i].spd;
				double px, py;
				for (j = 0; j < cshot[i].spd / r; j++) {//�i�񂾕��������蔻�蕪���[�v
					px = pre_x - getX();
					py = pre_y - getY();
					if (px*px + py * py < r*r) {
						cshot[i].flag = 0;//���̎��@�V���b�g������
						_hp -= cshot[i].power;//�e�̎��p���[��HP�����炷
						break;
					}
					pre_x += cos(cshot[i].angle)*r;
					pre_y += sin(cshot[i].angle)*r;
				}
			}
			else if (x*x + y * y < r*r)//�����蔻����Ȃ�
			{
				cshot[i].flag = 0;//���̎��@�V���b�g������
				_hp -= cshot[i].power;//�e�̎��p���[��HP�����炷
			}
		}
	}
	if (_hp <= 0)return false;
	return true;
}


