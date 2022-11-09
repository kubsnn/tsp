#pragma once

#include "libs.hpp"

using float64 = double;

class algorithm {
public:
	friend class tsp;

	inline algorithm(const vector2d<float64>& _Data) 
		: _Data(_Data)
	{ }

	inline virtual vector<size_t> solve() = 0;

protected:
	inline float64 _Calculate_length(const vector<size_t>& _Path) const {
		float64 _Path_len = 0;
		size_t _E_count = _Data.size();
		for (size_t i = 0; i < _E_count - 1; ++i) {
			_Path_len += _Data[_Path[i]][_Path[i + 1]];
		}
		_Path_len += _Data[_Path[_E_count - 1]][_Path[0]];
		return _Path_len;
	}

	const vector2d<float64> _Data;
};

template <class _Algorithm>
concept algorithm_type = std::derived_from<_Algorithm, algorithm>;

template <size_t _MaxNumLength>
inline void print_matrix(const vector2d<double>& _Matrix) {
	for (const auto& row : _Matrix) {
		cout << "[ ";
		for (const auto& col : row) {
			cout << std::setw(_MaxNumLength + 2) << col << " ";
		}
		cout << "]" << endl;
	}
}