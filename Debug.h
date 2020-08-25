#pragma once
#ifdef DEBUG
#define log(x) std::cout << x << std::endl
#include <iostream>
#else
#define log(x)
#endif