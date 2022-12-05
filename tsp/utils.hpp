#pragma once

#include "libs.hpp"
#include "colors.h"


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

inline void clear_progress(const vector2d<float64>& _Data, const char* _Filename) {
	std::ofstream _File(_Filename);
	_File.close();
}

inline void write_progress(const vector2d<float64>& _Data, const vector2d<size_t>& _Path, const char* _Filename) {
#ifdef DEBUG1
	std::ofstream _File(_Filename, std::ios::app);
	if (!_File.is_open()) {
		throw std::runtime_error("Cannot open file: " + string(_Filename));
	}

	size_t _E_count = _Data.size();
	for (size_t i = 0; i < _Path.size(); ++i) {
		for (size_t j = 0; j < _E_count; ++j) {
			_File << _Path[i][j] << ' ' << _Path[i][(j + 1) % _E_count] << endl;
		}
	}

	_File.close();
#endif
}

inline float64 calculate_average_distance(const vector2d<float64>& _Data) {
	float64 _Sum = 0.0;
	for (size_t i = 0; i < _Data.size(); ++i) {
		_Sum += std::accumulate(_Data[i].begin() + i + 1, _Data[i].end(), 0.0);
	}
	size_t _Elem_count = _Data.size() * (_Data.size() - 1) / 2;
	return _Sum / _Elem_count;
}

inline void print_path(const vector<size_t>& _Path, float64 _Path_len) {
	cout << color::white << "[\n  ";
	for (size_t i = 0; i < _Path.size(); ++i) {
		cout << color::darkgreen << _Path[i] << color::gray << ", ";
		if ((i + 1) % 12 == 0) cout << "\n  ";
	}
	cout << color::darkgreen << _Path[0] << color::white << endl;
	cout << color::white << "]\n";
	
	cout << color::white << "Path length: " << color::green << _Path_len << color::gray << "\n\n" << endl;
}

template <algorithm_type _Algo>
inline void print_algorithm_name() {
	auto _Prietify_name = [](string _Name) {
		std::replace(_Name.begin(), _Name.end(), '_', ' ');
		_Name.erase(std::find_if(_Name.rbegin(), _Name.rend(), [](char c) { return !std::isspace(c); }).base(), _Name.end());
		_Name[0] = std::toupper(_Name[0]);
		for (auto& e : _Name) {
			if (e == ' ') *(&e + 1) = std::toupper(*(&e + 1));
		}
		return _Name;
	};
	cout << color::white << "Algorithm: " << color::green << _Prietify_name(typeid(_Algo).name() + 6) << color::gray << endl;
}

inline void check_for_duplicates(const vector<size_t>& _Path) {
	for (size_t i = 0; i < _Path.size(); ++i) {
		for (size_t j = i + 1; j < _Path.size(); ++j) {
			if (_Path[i] == _Path[j]) {
				std::cerr << color::red << "Duplicate found: " << _Path[i] << " at " << i << " and " << j << color::gray << endl;
			}
		}
	}
}