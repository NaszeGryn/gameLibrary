#pragma once
#ifdef DEBUG
#define gL_log(x) std::cout << x << std::endl
#include <iostream>
#else
#define gL_log(x)
#endif