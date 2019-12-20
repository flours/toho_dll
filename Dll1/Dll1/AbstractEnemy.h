#pragma once

#include "Task.h"

#include "EnemyMover.h"
#include "Shot.h"
#include "cShot.h"

class Player;

class AbstractEnemy : public Task
{
public:
	AbstractEnemy(float x, float y, std::shared_ptr<Player> player);
	virtual ~AbstractEnemy() = default;
	void initialize();
	bool update() override;
	bool hit_judge(cshot_t[cShot::CSHOT_MAX]);

	float getX() const { return _x; }
	void  setX(float x) { _x = x; }
	float getY() const { return _y; }
	void  setY(float y) { _y = y; }
	int   getCounter() const { return _counter; }
	void  setSpeed(float speed) { _speed = speed; }
	float getSpeed() const { return _speed; }
	void  setAngle(float angle) { _angle = angle; }
	float getAngle() const { return _angle; }
	int   getMovePatternID() const { return _movePatternID; }
	int   getShotPatternID() const { return _shotPatternID; }
	int getSize();
	Shot* getShot() { return &_shot; }


protected:
	virtual void setSize() = 0;
	bool isInside() const;

	EnemyMover _mover;
	std::shared_ptr<Player> _player;

	float _x, _y;//座標
	float _speed;//速さ
	float _angle;//角度

	int _counter;//カウンタ
	int _width; //幅
	int _height;//高さ
	int _hp;

	Shot _shot;
	int _movePatternID;//移動パターン
	int _shotPatternID;//弾幕パターン
};