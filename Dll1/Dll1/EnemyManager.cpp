#include "EnemyManager.h"
#include "Define.h"
#include "SmallEnemy.h"
#include "NormalEnemy.h"
#include "BigEnemy.h"
#include "Player.h"

using namespace std;

EnemyManager::EnemyManager(std::shared_ptr<Player> player)
{
	for (auto enemy : _list) {
		enemy->initialize();
	}
	_player = player;
}	

bool EnemyManager::update()
{
	if (cnt % 100 == 0) {
		_list.emplace_back(make_shared<SmallEnemy>(Define::CENTER_X-100, -10, _player));
		_list.emplace_back(make_shared<NormalEnemy>(Define::CENTER_X, -10, _player));
		_list.emplace_back(make_shared<BigEnemy>(Define::CENTER_X+100, -10, _player));
	}

	cnt++;

	for (auto it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	return true;
}

bool EnemyManager::hit_judge()
{
	for (auto it = _list.begin(); it != _list.end();) {
		_player->hit_judge((*it)->getShot()->getBullet());
		if ((*it)->hit_judge(_player->getcShot()->getcshot()) == false) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	return true;
}

void EnemyManager::draw() const

{
	for (const auto enemy : _list) {
		enemy->draw();
	}
}