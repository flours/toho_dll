#pragma once

#include<memory>

class Player;

typedef struct {
	int flag, power, cnt, knd;
	double x, y, angle, spd;
}cshot_t;

class cShot
{
public:
	cShot(Player*  player);
	virtual ~cShot() = default;
	void draw() const;
	void shot();
	static const int CSHOT_MAX = 200;
	cshot_t* getcshot() { return cshot; }

private:

	cshot_t cshot[CSHOT_MAX];

	int power;
	int shot_cnt;

	void shot0();
	void shot1();
	int search_cshot();

	void calc_cshot();
	void enter_shot();

	Player* _player;
	
	static const int cshot0pos_x[4];
	static const int cshot0pos_y[4];
	static const int cshot0num[2];
};