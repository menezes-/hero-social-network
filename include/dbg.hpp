#pragma once
#ifndef NDEBUG

#include <iostream>
#define DEBUG(x) std::cout << x
#else
#  define DEBUG(x) do {} while (0)
#endif