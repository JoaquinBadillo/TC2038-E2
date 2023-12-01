#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace utils {
  	typedef std::vector<std::vector<int>> AdjMatrix;
	
  	std::pair<AdjMatrix, std::vector<std::pair<double, double>>> read(std::string filename) {
    	std::ifstream file;
      	file.open(filename);

		AdjMatrix graph;

		if (!file.is_open()) {
			std::cout << "Error: File not found" << std::endl;
			exit(1);
		}

		std::string line;

		std::getline(file, line);
		int nodes = std::stoi(line);

		for (int i = 0; i < nodes; ++i)
			graph.push_back(std::vector<int>(nodes));

		for (int i = 0; i < nodes; ++i) {
			for (int j = 0; j < nodes - 1; ++j) {
				std::getline(file, line, ' ');
				int weight = std::stoi(line);
				graph[i][j] = weight;
			}
				std::getline(file, line);
				int weight = std::stoi(line);
				graph[i][nodes - 1] = weight;
		}

		std::vector<std::pair<double, double>> coords;

		for (int i = 0; i < nodes; ++i) {
			std::getline(file, line, '(');
			std::getline(file, line, ',');

			double x = std::stod(line);

			std::getline(file, line, ')');
			double y = std::stod(line);
			coords.push_back(std::make_pair(x, y));

			std::getline(file, line);
		}

		file.close();

		return {graph, coords};
  	}
}

#endif
