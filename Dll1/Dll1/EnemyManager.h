#pragma once

#include "Task.h"
#include <memory>
#include <list>
#include "AbstractEnemy.h"
#include "SmallEnemy.h"
#include "Player.h"

class EnemyManager : public Task
{
public:
	EnemyManager(std::shared_ptr<Player> player);
	virtual ~EnemyManager() = default;
	bool update() override;
	bool hit_judge();
	void draw() const override;

private:
	int cnt;
	//�G�̈ʒu���擾���邽��Player���擾
	std::shared_ptr<Player> _player;
	std::list<std::shared_ptr<AbstractEnemy>> _list;
};
