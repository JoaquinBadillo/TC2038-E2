#include "./lib/utils.hpp"
#include "./lib/mst.hpp"
#include "./lib/tsp.hpp"
#include "./lib/search.hpp"

int main(int argc, char *argv[]) {
  std::string filename = argc > 1 ? argv[1] : "input.txt";
  std::pair<utils::AdjMatrix, std::vector<std::pair<double, double>>> data =
    utils::read(filename);

  utils::AdjMatrix graph = data.first;
  std::vector<std::pair<double, double>> coords = data.second;

  std::cout << "Solving part 1: (MST)" << std::endl;
  p1::mst(graph);
  std::cout << std::endl;

  std::cout << "Solving part 2: (TSP)" << std::endl;
  char start;
  std::cout << "Enter starting node (A, B, C,...): ";
  std::cin >> start;
  static_cast<int>(start);

  p2::tsp(graph, start - 65);
  std::cout << std::endl;

  std::cout << "Solving part 3: Closest Point" << std::endl;
  p3::Point closest = p3::findClosestPair(coords);
  std::cout
    << "Closest point:\n"
    << "("
    << closest.first
    << ", "
    << closest.second
    << ")"
    << std::endl;
  return 0;
}
