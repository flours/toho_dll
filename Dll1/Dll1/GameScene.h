#pragma once

#include "Player.h"
#include "AbstractScene.h"
#include<memory>
#include "EnemyManager.h"

class GameScene : public AbstractScene
{
public:
	const static char* ParameterTagStage;//パラメータのタグ「ステージ」
	const static char* ParameterTagLevel;//パラメータのタグ「レベル」

	GameScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameScene() = default;

	void update() override;
	void draw() const override;

private:
	int _level;
	std::shared_ptr<Player> _player;
	std::shared_ptr<EnemyManager> _enemyManager;

};