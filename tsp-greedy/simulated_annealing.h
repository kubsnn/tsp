#pragma once

#include "libs.hpp"
#include "utils.hpp"
#include "greedy.h"
#include <random>


class simulated_annealing : public algorithm {
public:
	using algorithm::_Data;

	inline static float64 Temp_init = 5000;
	inline static float64 Alpha = 0.003;
	inline static float64 Temp_min = 1;

	inline simulated_annealing(const vector2d<float64>& _Data)
		: algorithm(_Data)
	{ }

	inline vector<size_t> solve() override {
		return _Solve();
	}

private:
	inline vector<size_t> _Solve() {
		greedy _Greedy(_Data);
		auto _Path = _Greedy.solve();

	
		std::default_random_engine _Engine(time(NULL));
		std::uniform_real_distribution<float64> _F64_dist(0., 100.);
		//std::uniform_int_distribution<size_t> _U32_dist
		
		size_t _E_count = _Data.size();
		float64 _Path_len = _Calculate_length(_Path);
		float64 _Temperature = Temp_init;
		float64 _Cooling_rate = Alpha;
		float64 _Min_temperature = Temp_min;

		while (_Temperature > _Min_temperature) {
			size_t _First = rand() % _E_count;
			size_t _Second = rand() % _E_count;
			std::swap(_Path[_First], _Path[_Second]);

			float64 _New_path_len = _Calculate_length(_Path);
			float64 _Delta = _New_path_len - _Path_len;
			if (_Delta < 0) {
				_Path_len = _New_path_len;
			} else {
				float64 _Probability = exp(-_Delta / _Temperature);
				if (_Rnd(_F64_dist, _Engine) < _Probability * 100) {
					_Path_len = _New_path_len;
				} else {
					std::swap(_Path[_First], _Path[_Second]);
				}
			}
			_Temperature *= 1 - _Cooling_rate;
		}
		return _Path;
	}
	
	inline float64 _Rnd(std::uniform_real_distribution<>& _Dist, std::default_random_engine& _Engine) {
		return _Dist(_Engine);
	}
};