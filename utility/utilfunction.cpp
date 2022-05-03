#include "utilfunction.h"
#include <algorithm>

std::vector<Edge> ComputeActualPath(const std::vector<Edge> &tracePath) {
  if (tracePath.size() == 0 || tracePath.size() == 1)
    return tracePath;

  std::vector<Edge> actualPath{*(tracePath.rbegin())};
  for (auto curr = tracePath.rbegin() + 1; curr != tracePath.rend(); curr++) {
    auto &prev = *actualPath.rbegin();

    if (curr->End != prev.Start) {
      continue;
    }
    actualPath.push_back(*curr);
  }
  std::reverse(actualPath.begin(), actualPath.end());

  return actualPath;
}

void displayPath(const Graph &graph, const std::vector<Edge> path,
                 std::string_view message) {
  std::cout << message << "\n";
  if (path.empty()) 
    return;
  
  std::cout << graph[path[0].Start] << " -> ";
  for (size_t i = 0; i < path.size() - 1; ++i) {
    std::cout << graph[path[i].End] << " -> ";
  }
  std::cout << graph[path.rbegin()->End] << std::endl;
}