#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include "Display.h"

/*!
* @brief �Q�[���̏�������
*/
bool SystemMain::initialize() const
{

//	SetWindowText("�l�����_�^2");				//�E�B���h�E�^�C�g����t����
	const int COLOR_BIT = 32;					//�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
	return true;
}

/*!
* @brief DX���C�u������Q�[���̏I������
*/
void SystemMain::finalize() const
{
}

/*!
* @brief ���C������
*/
void SystemMain::main() const
{
//	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
	//TODO ��ʕ\��


	looper.loop();
}