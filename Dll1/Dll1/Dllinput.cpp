#include<Dllinput.h>

int Dllinput::keys_array[256] = {0};

void Dllinput::input(int keys[256]) {
	for (int i = 0; i < 256; i++)
	{
		if (keys[i] == 0)	keys_array[i] = 0;
		else				keys_array[i] += keys[i];
	}
}

int Dllinput::input_check(int key) {
	return keys_array[key];
}
