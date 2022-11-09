// tsp-greedy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "loader.hpp"
#include "utils.hpp"
#include "greedy.h"
#include "simulated_annealing.h"
#include "tsp.hpp"

#include <iostream>
#include <iomanip>


int main()
{
	srand(time(NULL));
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2) << std::setfill(' ') << std::fixed;

    loader wgraph_loader;
	auto graph = wgraph_loader.create_matrix(path);
	
	simulated_annealing::Temp_init = 60;

	tsp solver(std::move(graph));
	solver.solve<simulated_annealing>();
	solver.solve<greedy>();

	
}
