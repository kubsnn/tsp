#pragma once

#include "libs.hpp"

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