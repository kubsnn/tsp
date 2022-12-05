#pragma once

#include "libs.hpp"
#include "utils.hpp"
#include <algorithm>

class brute : public algorithm {
	
public:
	using algorithm::_Data;

	brute(const vector2d<float64>& _Data)
		: algorithm(_Data)
	{ }

	inline vector<size_t> solve() override {
		return _Solve_brute();
	}
	
private:
	inline vector<size_t> _Solve_brute() const {
		size_t _E_count = _Data.size();
		vector<size_t> _Path(_E_count);
		for (size_t i = 0; i < _E_count; ++i) {
			_Path[i] = i;
		}

		float64 _Min = FLOAT64_MAX;
		vector<size_t> _Best_path;

		do {
			float64 _Path_len = _Calculate_length(_Path);
			if (_Path_len < _Min) {
				_Min = _Path_len;
				_Best_path = _Path;
			}
		} while (std::next_permutation(_Path.begin() + 1, _Path.end()));

		return _Best_path;
	}
};