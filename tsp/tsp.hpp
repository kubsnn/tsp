#pragma once

#include "libs.hpp"
#include "utils.hpp"

#include <algorithm>

class tsp {
public:
	inline tsp(vector2d<float64>&& _Graph)
		: _Data(std::move(_Graph))
	{ }

	template <algorithm_type _Algorithm>
	inline void solve() const {
		_Algorithm _Alg(_Data);
		
		auto _Path = _Alg.solve();
		
		cout << (typeid(_Alg).name() + 6) << endl;

		auto _Cpy = _Path;
		std::sort(_Cpy.begin(), _Cpy.end());
		bool hasDuplicates = std::adjacent_find(_Cpy.begin(), _Cpy.end()) != _Cpy.end();
		cout << "Duplicates? " << (hasDuplicates ? "YES" : "NO") << endl;

		cout << "Path: ";
		for (const auto& _Node : _Path) {
			cout << _Node << " ";
		}
		cout << endl;
		
		cout << "Path length: " << _Alg._Calculate_length(_Path) << endl << endl;
	}

private:
	const vector2d<float64> _Data;
};