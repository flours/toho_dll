// Dll1.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//


#include<Header.h>
#include "SystemMain.h"
#include"Dllinput.h"
#include"Display.h"
#include<opencv2/opencv.hpp>
#include<stdio.h>
SystemMain main_system;

void hello() {
	std::cout << "Hello world" << std::endl;
}

void init() {
	main_system.initialize();
}

void finalize() {
	main_system.finalize();
}


void input(int keys[256]) {
	Dllinput::input(keys);	
}

int main() {

	main_system.main();
	return 0;
}


void observe(unsigned char *img, int* reward, int* life, int* done) {
	memcpy(img, Display::main_image.datastart,sizeof(unsigned char)*640*480*3);
	Display::getdatas(reward,done,life);
}

void reset()
{
	Display::reset();
}