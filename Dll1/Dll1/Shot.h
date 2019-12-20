#pragma once

#include "Bullet.h"
#include <vector>
#include "Player.h"

class AbstractEnemy;

class Shot
{
public:
	Shot(std::shared_ptr<Player> player);
	virtual ~Shot() = default;
	void shot(AbstractEnemy *enemy);
	void draw(AbstractEnemy *enemy) const;
	bool update(AbstractEnemy *enemy);
	bullet_t* getBullet() { return bullet; };
	static const int SHOT_BULLET_MAX = 1000;


private:

	bullet_t bullet[SHOT_BULLET_MAX];

	std::shared_ptr<Player> _player;
	bool bullet_inside();
	double shotatan2(AbstractEnemy *enemy);
	int shot_search();
	void setFunction();
	void Bullet_calc();

	typedef void(Shot::*FUNC)(AbstractEnemy* enemy);
	std::vector<FUNC> _shotPattern;

	void enter_shot(AbstractEnemy *enemy);

	//フラグ、種類、カウンタ、どの敵から発射されたかの番号
	int flag, knd, cnt, num;
	//ベース角度、ベーススピード
	double base_angle, base_spd;
	void shotPattern00(AbstractEnemy *enemy);
};