#pragma once

#include "libs.hpp"
#include "utils.hpp"
#include "simulated_annealing.hpp"
#include "tsp.hpp"

class settings {
public:
	inline settings(const vector2d<float64>& _Graph)
		: _Data(_Graph)
	{ }
	
	inline void apply_precision_level(size_t _Precision_lvl) {
		if (_Precision_lvl == 1) set_parameters_for_fast_solution();
		else if (_Precision_lvl == 2) set_parameters_for_medium_solution();
		else if (_Precision_lvl == 3) set_parameters_for_precise_solution();
		else if (_Precision_lvl == 4) set_parameters_for_precise_solution_many_cities();
		else if (_Precision_lvl == 5) set_settings(10.2e4, 21, 0.08); // tsp 1000
		else if (_Precision_lvl == 6) set_settings(121e4, 11, 0.04);
		else if (_Precision_lvl == 7) set_settings(30e4, 3, 0.04);
		else throw std::runtime_error("Invalid precision level");
	}

	inline void set_parameters_for_fast_solution() const {
		set_settings(6e3, 12, 1);
	}

	inline void set_parameters_for_medium_solution() const {
		set_settings(1.6e4, 4, 1.3);
	}

	inline void set_parameters_for_precise_solution() const {
		set_settings(6e4, 10, 2);
	}
	
	inline void set_parameters_for_precise_solution_many_cities() const {
		set_settings(5e4, 23, 1.6);
	}

private:
	inline void set_settings(size_t _Iters_per_edge, float64 Init_temp_coef, float64 _Out_iters_coef) const {
		const float64 _Avg_distance = calculate_average_distance(_Data);

		simulated_annealing::Iterations = std::min(_Data.size(), (size_t)100) * _Out_iters_coef;
		simulated_annealing::Temp_init = _Avg_distance / Init_temp_coef;
		simulated_annealing::Temp_min = 1.08;
		simulated_annealing::Alpha = _Predict_cooling_rate(simulated_annealing::Temp_init, _Iters_per_edge * _Data.size());
	}

	inline float64 _Predict_cooling_rate(float64 _Initial_temp, float64 _Iteration_count) const {
		return 1.0 - pow(1.08 / _Initial_temp, 1.0 / _Iteration_count);
	}

	const vector2d<float64>& _Data;
};