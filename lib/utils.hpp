#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace utils {
  	typedef std::vector<std::vector<int>> AdjMatrix;
	
  	AdjMatrix read(std::string filename) {
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

		file.close();

		return graph;
  	}
}

#endif
