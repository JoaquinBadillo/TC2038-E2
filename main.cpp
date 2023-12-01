#include "./lib/utils.hpp"
#include "./lib/mst.hpp"
#include "./lib/tsp.hpp"

int main (int argc, char *argv[]) {
  std::string filename = argc > 1 ? argv[1] : "input.txt";
  utils::AdjMatrix graph = utils::read(filename);
  p1::mst(graph);

  char start;
  std::cout << "Enter starting node (A, B, C,...): "; 
  std::cin >> start;

  p2::tsp(graph, (int)(start) - 65);

  return 0;
}
