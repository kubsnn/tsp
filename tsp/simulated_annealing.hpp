#pragma once

#include "libs.hpp"
#include "utils.hpp"
#include "greedy.hpp"
#include <random>


class simulated_annealing : public algorithm {
public:
	using algorithm::_Data;

	inline static float64 Temp_init = 1e2;
	inline static float64 Alpha = 3e-6;
	inline static float64 Temp_min = 1.15;
	inline static size_t Iterations = 15;

	inline simulated_annealing(const vector2d<float64>& _Data)
		: algorithm(_Data)
	{ }

	inline vector<size_t> solve() override {
		auto _Best_greedy = _Get_best_greedy_solution();
		auto _Best_random = _Get_best_random_solution();

		if (_Calculate_length(_Best_greedy.back()) < _Calculate_length(_Best_random.back())) {
			write_progress(_Data, _Best_greedy, "results.txt");
			return _Best_greedy.back();
		} else {
			write_progress(_Data, _Best_random, "results.txt");
			return _Best_random.back();
		}
	}

private:
	inline vector2d<size_t> _Get_best_greedy_solution() {
		greedy _Greedy(_Data);
		vector2d<size_t> _Best_path_progress;
		float64 _Min_len = FLOAT64_MAX;
		
		size_t _Iters = std::min(Iterations, _Data.size());
		_Last_path_progress.reserve(_Iters);
		
		for (size_t i = 0; i < _Iters; ++i) {
			auto _Path = _Solve_path(_Greedy._Solve_greedy(i));
			float64 _Path_len = _Calculate_length(_Path);
			if (_Path_len < _Min_len) {
				_Min_len = _Path_len;
				_Best_path_progress = std::move(_Last_path_progress);
			}
			_Last_path_progress.clear();
		}

		return _Best_path_progress;
	}

	inline vector2d<size_t> _Get_best_random_solution() {
		vector2d<size_t> _Best_path_progress;
		float64 _Min_len = FLOAT64_MAX;

		size_t _Iters = Iterations + std::max((int64_t)Iterations - (int64_t)_Data.size(), 0i64);
		_Last_path_progress.reserve(_Iters);

		for (size_t i = 0; i < _Iters; ++i) {
			auto _Path = _Solve_path(_Generate_random_path());
			float64 _Path_len = _Calculate_length(_Path);
			if (_Path_len < _Min_len) {
				_Min_len = _Path_len;
				_Best_path_progress = std::move(_Last_path_progress);
			}
			_Last_path_progress.clear();
		}

		return _Best_path_progress;
	}

	inline vector<size_t> _Solve_path(vector<size_t> _Path) {
		std::default_random_engine _Engine(time(NULL));
		std::uniform_real_distribution<float64> _F64_dist(0., 100.);

		size_t _E_count = _Data.size();
		float64 _Path_len = _Calculate_length(_Path);
		float64 _Temperature = Temp_init;
		float64 _Cooling_rate = Alpha;
		float64 _Min_temperature = Temp_min;
		size_t _Mask = (1 << 13) - 1;
		int _Ctr = 1;
		while (_Temperature > _Min_temperature) {
			size_t _First = rand() % _E_count;
			size_t _Second = rand() % _E_count;

			float64 _New_path_len = _Update_and_calculate_new_path_length(_Path, _First, _Second, _Path_len);

			float64 _Delta = _New_path_len - _Path_len;
			if (_Delta < 0) {
				_Path_len = _New_path_len;
			}
			else {
				float64 _Probability = exp(-_Delta / _Temperature);
				if (_Rnd(_F64_dist, _Engine) < _Probability * 100.) {
					_Path_len = _New_path_len;
				}
				else {
					std::swap(_Path[_First], _Path[_Second]);
				}
			}
			_Temperature *= 1 - _Cooling_rate;
#ifdef DEBUG1	
			if ((++_Ctr & _Mask) == 0) {
				_Last_path_progress.emplace_back(_Path);
				//cout << "Temperature: " << _Temperature << endl;
			}
#endif
		}
		return _Path;
	}

	float64 _Update_and_calculate_new_path_length(vector<size_t>& _Path, size_t _First, size_t _Second, float64 _Prev_length) {
		size_t _E_count = _Data.size();
		float64 _Delta = 0;
		_Delta -= _Data[_Path[_First]][_Path[(_First + 1) % _E_count]];
		_Delta -= _Data[_Path[_First]][_Path[(_First + _E_count - 1) % _E_count]];
		_Delta -= _Data[_Path[_Second]][_Path[(_Second + 1) % _E_count]];
		_Delta -= _Data[_Path[_Second]][_Path[(_Second + _E_count - 1) % _E_count]];
		std::swap(_Path[_First], _Path[_Second]);
		_Delta += _Data[_Path[_First]][_Path[(_First + 1) % _E_count]];
		_Delta += _Data[_Path[_First]][_Path[(_First + _E_count - 1) % _E_count]];
		_Delta += _Data[_Path[_Second]][_Path[(_Second + 1) % _E_count]];
		_Delta += _Data[_Path[_Second]][_Path[(_Second + _E_count - 1) % _E_count]];
		
		return _Prev_length + _Delta;
	}


	inline float64 _Rnd(std::uniform_real_distribution<>& _Dist, std::default_random_engine& _Engine) const {
		return _Dist(_Engine);
	}

	inline vector<size_t> _Generate_random_path() const {
		size_t _Len = _Data.size();
		vector<size_t> _Path(_Len);
		for (size_t i = 0; i < _Len; ++i) {
			_Path[i] = i;
		}
		std::shuffle(_Path.begin(), _Path.end(), std::default_random_engine(time(NULL)));
		return _Path;
	}

	vector2d<size_t> _Last_path_progress;
};