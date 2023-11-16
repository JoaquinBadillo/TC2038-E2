#ifndef TSP_H
#define TSP_H

#include "./utils.hpp"

namespace p2 {
    template<std::size_t n> void tsp(utils::AdjMatrix<n> adj_matrix);
}

#endif