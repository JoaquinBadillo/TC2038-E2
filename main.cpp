#include "./lib/utils.hpp"
#include "./lib/mst.hpp"
#include "./lib/tsp.hpp"

int main (int argc, char *argv[]) {
  std::string filename = argc > 1 ? argv[1] : "input.txt";
  utils::AdjMatrix graph = utils::read(filename);
  p1::mst(graph);

  std::cout << "Running TSP..." << std::endl;
  p2::tsp(graph, 0);
  return 0;
}
