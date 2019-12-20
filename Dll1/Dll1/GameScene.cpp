#include<iostream>
#include "GameScene.h"
#include "Macro.h"

const char* GameScene::ParameterTagStage = "ParameterTagStage";//パラメータのタグ「ステージ」
const char* GameScene::ParameterTagLevel = "ParameterTagLevel";//パラメータのタグ「レベル」

using namespace std;

GameScene::GameScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	_player = make_shared<Player>();
	_enemyManager = make_shared<EnemyManager>(_player);
	_level = parameter.get(ParameterTagLevel);
}

void GameScene::update()
{
	_player->update();
	_enemyManager->update();
	_enemyManager->hit_judge();
}

void GameScene::draw() const
{
	_player->draw();
	_enemyManager->draw();
}