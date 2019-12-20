#pragma once

#include<windows.h>


class Dllinput
{
private:
	static int keys_array[256];
public:
	static void input(int keys[256]);
	static int input_check(int key);
	static const int slow = VK_SHIFT;
	static const int shot = 'Z';
	static const int left = VK_LEFT;
	static const int right = VK_RIGHT;
	static const int up = VK_UP;
	static const int down = VK_DOWN;
};