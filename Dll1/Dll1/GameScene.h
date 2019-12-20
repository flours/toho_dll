#pragma once

#include "Player.h"
#include "AbstractScene.h"
#include<memory>
#include "EnemyManager.h"

class GameScene : public AbstractScene
{
public:
	const static char* ParameterTagStage;//�p�����[�^�̃^�O�u�X�e�[�W�v
	const static char* ParameterTagLevel;//�p�����[�^�̃^�O�u���x���v

	GameScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameScene() = default;

	void update() override;
	void draw() const override;

private:
	int _level;
	std::shared_ptr<Player> _player;
	std::shared_ptr<EnemyManager> _enemyManager;

};