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
		
		print_algorithm_name<_Algorithm>();

		check_for_duplicates(_Path);

		print_path(_Path, _Alg._Calculate_length(_Path));

		write_progress(_Data, { _Path }, "out.txt");
	}

private:
	const vector2d<float64> _Data;
};