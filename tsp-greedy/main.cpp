// tsp-greedy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "loader.hpp"
#include "utils.hpp"
#include "tsp.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2) << std::setfill(' ') << std::fixed;

    loader wgraph_loader;
	auto graph = wgraph_loader.create_matrix("test.txt");
	
	tsp solver(std::move(graph));
	solver.solve_greedy();
}
