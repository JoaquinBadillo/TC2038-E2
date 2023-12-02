#ifndef MST_H
#define MST_H

#include <vector>
#include <queue>
#include <unordered_set>
#include "./utils.hpp"

namespace p1 {
  typedef struct Edge {
    int id;
    int tag;
    int weight;
  } Edge;

  struct compare {
    bool operator()(Edge const& u, Edge const& v) const {
      return u.weight > v.weight;
    }
  };

  typedef std::priority_queue<Edge, std::vector<Edge>, compare> MinHeap;

  void mst(const utils::AdjMatrix& adj_matrix) {
    MinHeap pq;
    std::unordered_set<int> permanent;
    std::vector<Edge> mst;

    // weight organizes the heap, id (node) and tag (prev node) track edges
    pq.push({
      .id = 0,
      .tag = 0,
      .weight = 0
    });

    while (!pq.empty() && mst.size() < adj_matrix.size() - 1) {
      Edge current = pq.top();
      pq.pop();

      if (permanent.find(current.id) != permanent.end())
        continue;

      if (current.id != current.tag)
        mst.push_back(current);

      permanent.insert(current.id);

      for (int i = 0; i < adj_matrix.size(); i++) {
        if (i == current.id || permanent.find(i) != permanent.end())
          continue;

        pq.push({
          .id = i,
          .tag = current.id,
          .weight = adj_matrix[current.id][i]
        });
      }
    }

    // Print the MST (avoids returning the edge vector)
    for (auto& edge : mst) {
      std::cout << "("
            << edge.tag
            << ", "
            << edge.id
            << ")\t";
    }

    std::cout << std::endl;
  }

}

#endif
