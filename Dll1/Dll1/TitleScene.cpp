#include<iostream>
#include "TitleScene.h"
#include "GameScene.h"
#include "Define.h"
#include "Dllinput.h"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	if (Dllinput::input_check('E')) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Easy);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
		return;
	}
	if (Dllinput::input_check('N')) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Normal);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
		return;
	}
}

void TitleScene::update()
{
}

void TitleScene::draw() const
{
//	DrawString(100, 100, "ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor(255, 255, 255));
	std::cout << "title" << std::endl;
}