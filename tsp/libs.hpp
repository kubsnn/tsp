#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>

using std::vector;
using std::ifstream;
using std::string;
using std::pair;

using std::cout;
using std::endl;

template <class _Ty>
using vector2d = vector<vector<_Ty>>;

using float64 = double;

constexpr float64 FLOAT64_MAX = std::numeric_limits<float64>::max();
