// tsp-greedy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "loader.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(1) << std::setfill(' ') << std::fixed;

    loader wgraph_loader;
	auto graph = wgraph_loader.create_matrix("data.txt");
	print_matrix<4>(graph);
}
