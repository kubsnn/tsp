// tsp-greedy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#define DEBUG1
#include "loader.hpp"
#include "utils.hpp"
#include "greedy.hpp"
#include "simulated_annealing.hpp"
#include "brute.hpp"
#include "tsp.hpp"


#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
	if (argc > 2) {
		std::cerr << "Usage: tsp-greedy.exe <filename>" << std::endl;
		return 1;
	}

	auto path = argc == 2 ? argv[1] : "test.txt";

	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2) << std::setfill(' ') << std::fixed;

    loader wgraph_loader;
	auto graph = wgraph_loader.create_matrix(path);

	clear_progress(graph, "results.txt");

	tsp solver(std::move(graph));
	solver.solve<simulated_annealing>();
	solver.solve<greedy>();
	//solver.solve<brute>();
}
