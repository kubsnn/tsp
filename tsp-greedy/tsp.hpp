#pragma once

#include "libs.hpp"
#include "utils.hpp"

class tsp {
public:
	inline tsp(vector2d<double>&& _Graph)
		: _Data(std::move(_Graph))
	{ }
	
	inline void solve_greedy() const {
		_Solve_greedy();
	}

private:
	inline void _Solve_greedy() const {
		size_t _E_count = _Data.size();
		double _Path_len = 0;

		vector<bool> _Visited(_E_count, false);
		vector<size_t> _Path;

		_Path.emplace_back(0);
		_Visited[0] = true;

		size_t _Current = 0;
		for (size_t i = 1; i < _E_count; ++i) {
			size_t _Next = 0;
			double _Min = DBL_MAX;
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
		

		//Greedy
		cout << "Greedy: " << _Path_len << endl;
		cout << "Path: ";
		for (const auto& e : _Path) {
			cout << e << " ";
		}
		cout << endl;
		
		
	}

	const vector2d<double> _Data;
};