#pragma once
#include "Looper.h"

class SystemMain final
{
public:
	SystemMain() = default;
	~SystemMain() = default;
	bool initialize() const;
	void finalize() const;
	void main();
	Looper looper;
};