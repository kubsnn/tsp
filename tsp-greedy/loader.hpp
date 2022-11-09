#pragma once

#include "libs.hpp"

using point = pair<int, int>;

class loader
{
public:
	inline vector2d<double> create_matrix(const char* _Path) const {
		auto points = _Load_points(_Path);
		return _Convert_points_to_graph(points);
	}

private:
	inline vector2d<double> _Convert_points_to_graph(const vector<point>& _Points) const {
		vector2d<double> graph(_Points.size(), vector<double>(_Points.size(), 0.0));

		size_t _Count = _Points.size();
		for (size_t i = 0; i < _Count; ++i) {
			for (size_t j = i + 1; j < _Count; ++j) {
				double dis = _Calculate_distance(_Points[i], _Points[j]);
				graph[i][j] = dis;
				graph[j][i] = dis;
			}
		}
		
		return graph;
	}

	inline double _Calculate_distance(const point& _Point1, const point& _Point2) const {
		return sqrt(pow(_Point1.first - _Point2.first, 2) + pow(_Point1.second - _Point2.second, 2));
	}
	
	inline vector<point> _Load_points(const char* _Path) const {
		ifstream file(_Path);
		if (!file.is_open()) {
			throw std::exception("File not found!");
		}
		int count;
		file >> count;
		vector<point> points;
		points.reserve(count);
		int x, y;
		while (file >> x >> y) {
			points.emplace_back(x, y);
		}
		
		file.close();
		
		return points;
	}
};
	