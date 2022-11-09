#pragma once

#include "libs.hpp"
#include "utils.hpp"

class greedy : public algorithm {

public:
	using algorithm::_Data;

	greedy(const vector2d<float64>& _Data)
		: algorithm(_Data)
	{ }

	inline vector<size_t> solve() override {
		return _Solve_greedy();
	}

private:
	inline vector<size_t> _Solve_greedy() const {
		size_t _E_count = _Data.size();
		float64 _Path_len = 0;

		vector<bool> _Visited(_E_count, false);
		vector<size_t> _Path;

		_Path.emplace_back(0);
		_Visited[0] = true;

		size_t _Current = 0;
		for (size_t i = 1; i < _E_count; ++i) {
			size_t _Next = 0;
			float64 _Min = DBL_MAX;
			for (size_t j = 0; j < _E_count; ++j) {
				if (!_Visited[j] && _Data[_Current][j] < _Min) {
					_Min = _Data[_Current][j];
					_Next = j;
				}
			}
			_Path.emplace_back(_Next);
			_Visited[_Next] = true;
			_Path_len += _Min;
			_Current = _Next;
		}
		_Path_len += _Data[_Current][0];

		return _Path;
	}
};