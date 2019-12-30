#include "Looper.h"
#include "TitleScene.h"
#include "Error.h"
#include "GameScene.h"
#include "Macro.h"
#include "Display.h"
#include "Image.h"

using namespace std;

Looper::Looper()
{
	Image::getIns()->load();

	Parameter parameter;
	_sceneStack.push(make_shared<GameScene>(this, parameter)); //タイトル画面シーンを作ってpush
}
/*!
@brief スタックのトップのシーンの処理をする
*/



bool Looper::loop()
{
	if (Display::reset_flag)
	{
		reset();
		Display::reset_flag = 0;
	}
	Display::image_reset();
	_sceneStack.top()->update();    //スタックのトップのシーンを更新
	_sceneStack.top()->draw();      //スタックのトップのシーンを描画
	return true;
}

/*!
@brief シーン変更(各シーンからコールバックされる)
@param scene 変更するシーンのenum
@param parameter 前のシーンから引き継ぐパラメータ
@param stackClear 現在のシーンのスタックをクリアするか
*/

void Looper::reset() {
	while (!_sceneStack.empty()) {//スタックを全部ポップする(スタックを空にする)
		_sceneStack.pop();
	}
	Parameter parameter;
	_sceneStack.push(make_shared<GameScene>(this, parameter));
}

void Looper::onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear)
{
	if (stackClear) {//スタッククリアなら
		while (!_sceneStack.empty()) {//スタックを全部ポップする(スタックを空にする)
			_sceneStack.pop();
		}
	}
	switch (scene) {
	case Title:
		_sceneStack.push(make_shared<TitleScene>(this, parameter));
		break;
	case Game:
		_sceneStack.push(make_shared<GameScene>(this, parameter));
		break;
	default:
		//どうしようもないエラー発生
		ERR("あるはずのないシーンが呼ばれました");
		break;
	}
}