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
		auto _Res = _Solve_greedy(0);
		float64 _Path_len = _Calculate_length(_Res);
		for (size_t i = 1; i < _Data.size(); ++i) {
			auto _Tmp = _Solve_greedy(i);
			if (_Calculate_length(_Tmp) < _Path_len) {
				_Res = std::move(_Tmp);
				_Path_len = _Calculate_length(_Res);
			}
		}

		return _Res;
	}

private:
	inline vector<size_t> _Solve_greedy(size_t _Begin_index) const {
		size_t _E_count = _Data.size();
		float64 _Path_len = 0;

		vector<bool> _Visited(_E_count, false);
		vector<size_t> _Path;

		_Path.emplace_back(_Begin_index);
		_Visited[_Begin_index] = true;

		size_t _Current = 0;
		for (size_t i = 0; i < _E_count; ++i) {
			if (_Begin_index == i) {
				continue;
			}

			size_t _Next = 0;
			float64 _Min = FLOAT64_MAX;
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