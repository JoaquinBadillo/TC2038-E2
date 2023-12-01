#ifndef TSP_H
#define TSP_H

#include "./utils.hpp"
#include <queue>
#include <limits>
#include <unordered_set>

#define INF std::numeric_limits<int>::max()

namespace p2 {
    /* Auxiliary Functions */

    /* Get Children
        Returns the children in the search tree (nodes that have not been visited yet in a branch)
        O(V)
    */
    std::vector<int> getChildren(const utils::AdjMatrix& adj_matrix, int node, std::unordered_set<int>& visited) {
        std::vector<int> children;
        for (int i = 0; i < adj_matrix.size(); ++i) {
            if (adj_matrix[node][i] != 0 && visited.find(i) == visited.end()) {
                children.push_back(i);
            }
        }
        return children;
    }

    /* Heuristic
    
      Obtained from: https://www.youtube.com/watch?v=1FEP_sNb62k&ab_channel=AbdulBari
      O(V^2)
    */
    int reduce(utils::AdjMatrix adj_matrix, std::unordered_set<int> visited, int node, int prev) {                
        int cost = 0;
        utils::AdjMatrix reduced = adj_matrix;

        reduced[node][prev] = INF;

        //Reduce rows
        for (int i = 0; i < reduced.size(); ++i) {
            int min = INF;
            // Ignore visited nodes (rows)
            if (visited.find(i) != visited.end())
                continue;

            // Find minimum (without checking self)
            for (int j = 0; j < reduced.size(); ++j) {
                if (i != j)
                    min = std::min(min, reduced[i][j]);
            }

            // Only update if there is a valid minimum
            if (min == INF)
                continue;

            // Update row reducing by minimum (without updating self)
            for (int j = 0; j < reduced.size(); ++j) {
                if (i != j && reduced[i][j] != INF)
                    reduced[i][j] -= min;
            }

            cost += min;
        }

        //Reduce columns
        for (int i = 0; i < reduced.size(); ++i) {
            int min = INF;

            // Find minimum (ignoring self and visited rows)
            for (int j = 0; j < reduced.size(); ++j) {
                if (i == j || visited.find(j) != visited.end())
                    continue;

                min = std::min(min, reduced[j][i]);
            }

            // Only update if there is a valid minimum
            if (min == INF)
                continue;

            for (int j = 0; j < reduced.size(); ++j) {
                if (i == j || visited.find(j) != visited.end() || reduced[i][j] == INF)
                    continue;

                reduced[j][i] -= min;
            }

            cost += min;
        }


        int prev_cost = prev < 0 ? 0 : reduced[prev][node];
        std::cout << "Reduced rows and cols" << std::endl;

        for (auto row : reduced) {
            for (auto col : row) {
                std::cout << col << " ";
            }
            std::cout << std::endl;
        }

        return cost;
    }

    typedef struct Element {
        int node;
        int cost;
        int level;
        std::unordered_set<int> visited;
        utils::AdjMatrix reduced;
    } Element;

    struct compare {
        bool operator()(Element const& u, Element const& v) const {
            return u.cost > v.cost;
        }
    };

    void tsp(utils::AdjMatrix& adj_matrix, int start) {
        int best = INF;
        std::unordered_set<int> visited = {-1};
        std::priority_queue<Element, std::vector<Element>, compare> frontier;
        int data = reduce(adj_matrix, visited, start, -1);
        std::cout << "Reduced" << std::endl;
        
        // utils::AdjMatrix reduced = data.first;
        // int cost = data.second; 

        // frontier.push({
        //     .node = start, 
        //     .cost = cost, 
        //     .level = 0, 
        //     .visited = visited, 
        //     .reduced = reduced
        // });

        // while (!frontier.empty() && best > frontier.top().cost) {
        //     Element current = frontier.top();
        //     frontier.pop();

        //     if (current.level == adj_matrix.size() - 1) {
        //         if (current.cost + adj_matrix[current.node][start] < best) {
        //             best = current.cost + adj_matrix[current.node][start];
        //             std::cout << "Best: " << best << std::endl;
        //         }
        //         continue;
        //     }

        //     std::vector<int> children = getChildren(current.reduced, current.node, current.visited);

        //     for (int i = 0; i < children.size(); ++i) {
        //         std::unordered_set<int> visited = current.visited;
        //         visited.insert(current.node);
        //         std::pair<utils::AdjMatrix, int> data = reduce(current.reduced, visited, children[i], current.node);
        //         utils::AdjMatrix& reduced = data.first;
        //         int cost = data.second;

        //         frontier.push({
        //             .node = children[i], 
        //             .cost = cost + current.cost, 
        //             .level = current.level + 1, 
        //             .visited = visited, 
        //             .reduced = reduced
        //         });
        //     }
        // }

        // std::cout << "-> Best: " << best << std::endl;
    }
}

#endif
