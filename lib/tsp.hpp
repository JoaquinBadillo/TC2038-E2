#ifndef TSP_H
#define TSP_H

#include "./utils.hpp"
#include <limits>
#include <queue>
#include <algorithm>
#include <vector>

#define INT_MAX std::numeric_limits<int>::max()

namespace p2 {
    std::pair<utils::AdjMatrix, int> initialReducer(utils::AdjMatrix adj_matrix, 
                                                    int node) {
        if (adj_matrix.size() < 1)
            throw std::invalid_argument(
                    "Adjacency matrix must be at least 1x1");

        int cost = 0;
        utils::AdjMatrix reduced = adj_matrix;

        // Reduce rows
        for (int i = 0; i < reduced.size(); i++) {
            int min = INT_MAX;
            for (int j = 0; j < reduced[0].size(); j++) {
                if (reduced[i][j] >= INT_MAX)
                    continue;

                min = std::min(min, reduced[i][j]);
            }

            if (min != INT_MAX) {
                for (int j = 0; j < reduced.size(); j++) {
                    if (reduced[i][j] < INT_MAX)
                    reduced[i][j] -= min;
                }
                cost += min;
            }
        }

        // Reduce columns
        for (int i = 0; i < reduced[0].size(); i++) {
            int min = INT_MAX;
            for (int j = 0; j < reduced.size(); j++) {
                if (reduced[j][i] >= INT_MAX)
                    continue;

                min = std::min(min, reduced[j][i]);
            }

            if (min != INT_MAX) {
                for (int j = 0; j < reduced[0].size(); j++) {
                    if (reduced[j][i] < INT_MAX)
                    reduced[j][i] -= min;
                }
                cost += min;
            }
        }

        return std::make_pair(reduced, cost);
    }

    /* 
        O(V^2)
    */
    std::pair<utils::AdjMatrix, int> reducer(utils::AdjMatrix adj_matrix, int node, int prev, int prev_cost) {
        if (adj_matrix.size() < 1) {
            throw std::invalid_argument(
                "Adjacency matrix must be at least 1x1");
        }

        int cost = adj_matrix[prev][node];
        utils::AdjMatrix reduced = adj_matrix;

        // Kill them all
        for (int j = 0; j < reduced[0].size(); j++) {
            reduced[prev][j] = INT_MAX;
            reduced[j][node] = INT_MAX;
        }

        reduced[node][prev] = INT_MAX;

        // Reduce rows
        for (int i = 0; i < reduced.size(); i++) {
            int min = INT_MAX;
            for (int j = 0; j < reduced[0].size(); j++) {
                if (reduced[i][j] >= INT_MAX)
                    continue;

                min = std::min(min, reduced[i][j]);
            }

            if (min != INT_MAX) {
                for (int j = 0; j < reduced.size(); j++) {
                    if (reduced[i][j] < INT_MAX)
                    reduced[i][j] -= min;
                }
                cost += min;
            }
        }

        // Reduce columns
        for (int i = 0; i < reduced[0].size(); i++) {
            int min = INT_MAX;
            for (int j = 0; j < reduced.size(); j++) {
                if (reduced[j][i] >= INT_MAX)
                    continue;

                min = std::min(min, reduced[j][i]);
            }

            if (min != INT_MAX) {
                for (int j = 0; j < reduced[0].size(); j++) {
                    if (reduced[j][i] < INT_MAX)
                    reduced[j][i] -= min;
                }
                cost += min;
            }
        }

        return std::make_pair(reduced, cost + prev_cost);
    }

    typedef struct Element {
        int node;
        int cost;
        int level;
        utils::AdjMatrix reduced;
        std::vector<int> path;
    } Element;

    struct compare {
        bool operator()(Element const& u, Element const& v) const {
            return u.cost > v.cost;
        }
    };

    void tsp(utils::AdjMatrix adj_matrix, int start) {
        utils::AdjMatrix initial = adj_matrix;

        for (int i = 0; i < initial.size(); i++) {
            initial[i][i] = INT_MAX;
        }

        int best = INT_MAX;

        Element bestElement = {
            .node = -1,
            .cost = INT_MAX,
            .level = -1,
            .reduced = initial,
            .path = {}
        };

        std::pair<utils::AdjMatrix, int> reduced = initialReducer(initial, 0);
        std::priority_queue<Element, std::vector<Element>, compare> pq;
        pq.push({
            .node = start,
            .cost = reduced.second,
            .level = 0,
            .reduced = reduced.first,
            .path = {start}
        });

        while (!pq.empty() && pq.top().cost < best) {
            Element current = pq.top();
            pq.pop();

            if (current.level == adj_matrix.size() - 1) {
                best = std::min(best, current.cost + adj_matrix[current.node][start]);
                bestElement = current;
                continue;
            }

            for (int i = 0; i < current.reduced.size(); i++) {
                if (i == current.node)
                    continue;

                int min = INT_MAX;
                for (int j = 0; j < current.reduced[0].size(); j++) {
                    if (current.reduced[i][j] >= INT_MAX)
                        continue;

                    min = std::min(min, current.reduced[i][j]);
                }

                if (min < INT_MAX) {
                    std::pair<utils::AdjMatrix, int> reduced = reducer(current.reduced, i, current.node, current.cost);
                    std::vector<int> path = current.path;
                    path.push_back(i);

                    pq.push({
                        .node = i,
                        .cost = reduced.second,
                        .level = current.level + 1,
                        .reduced = reduced.first,
                        .path = path
                    });
                }
            }
        }

        int length = 0;
        std::cout << "Path: ";

        int prev = -1;
        for (auto node : bestElement.path) {
            if (prev != -1)
                length += adj_matrix[prev][node];
            prev = node;
            std::cout << (char)(node + 65) << " ";
        }

        std::cout << (char)(start + 65) << std::endl;

        length += adj_matrix[prev][start];

        std::cout << "Length: " << length << std::endl;
    }
}

#endif
