#pragma once


#include<windows.h>
#include<iostream>




#ifdef TOHO_EXPORTS
#define TOHO_API __declspec(dllexport)
#else
#define TOHO_API __declspec(dllimport)
#endif

extern "C" TOHO_API int main();
extern "C" TOHO_API void hello();
extern "C" TOHO_API void init();
extern "C" TOHO_API void finalize();
extern "C" TOHO_API void reset();
extern "C" TOHO_API void input(int keys[256]);
extern "C" TOHO_API void observe(unsigned char *img, int *reward, int *life, int *done);