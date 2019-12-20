#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include "Display.h"

/*!
* @brief ゲームの初期処理
*/
bool SystemMain::initialize() const
{

//	SetWindowText("四聖龍神録2");				//ウィンドウタイトルを付ける
	const int COLOR_BIT = 32;					//色のbit数。通常32で良いが軽くするなら16にする
	return true;
}

/*!
* @brief DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{
}

/*!
* @brief メイン処理
*/
void SystemMain::main() const
{
//	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
	//TODO 画面表示


	looper.loop();
}