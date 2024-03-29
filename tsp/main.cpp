﻿// tsp-greedy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
//#define DEBUG1 // zapisywanie postepu sciezki do pliku
#define IGNORE_RANDOM_SOLUTIONS // to warto raczej miec zdefiniowane, bo te losowe rozwiazania sa zwykle gorsze
//#define NO_PROGRESSBAR // to tez raczej zdefiniowac jak chcesz uzywac outputu do swojego programu
#define NO_ARGS // jak odpalasz w visualu to pewnie bedzie latwiej z tym
#include "loader.hpp"
#include "utils.hpp"
#include "greedy.hpp"
#include "simulated_annealing.hpp"
#include "brute.hpp"
#include "tsp.hpp"
#include "settings.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>

int main(int argc, char* argv[])
{
#ifndef NO_ARGS
	if (argc < 2) {
		std::cerr << "Usage: tsp-greedy.exe <filename> <presicion_level (1-3)>" << std::endl;
		return 1;
	}
	auto precision_lvl = argc > 2 ? (int)std::atof(argv[2]) : 1;
#else
	int precision_lvl = 7;
#endif
	const auto path = argc > 1 ? argv[1] : "tsp500.txt";
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2) << std::setfill(' ') << std::fixed;

    loader wgraph_loader;
	auto graph = wgraph_loader.create_matrix(path);
	size_t n = graph.size();

	settings settings(graph);
	settings.apply_precision_level(precision_lvl);
	
#ifdef DEBUG1
	clear_progress(graph, "results.txt");
#endif
	
	tsp solver(std::move(graph));
	
	solver.solve<simulated_annealing>(); 
	
	solver.solve<greedy>();
	
	if (n < 14) solver.solve<brute>();

}
