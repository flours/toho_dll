#pragma once

#include "Error.h"



#define ERR(str) Error::finish(str,(__FUNCTION__),__LINE__)