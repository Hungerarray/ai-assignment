#include <iostream>
#include <algorithm>
#include <deque>
#include <array>

constexpr uint32_t VERTCOUNT = 7;
enum Vertex { S, A, B, C, D, H, G };
char VertexName(Vertex v) {
  switch(v) {
    case S:
      return 'S';
    case A:
      return 'A';
    case B:
      return 'B';
    case C:
      return 'C';
    case D:
      return 'D';
    case H:
      return 'H';
    case G:
      return 'G';
    default:
      return '-';
  }
}

struct Path {
  std::deque<Vertex> path;
  uint64_t cost;
};

int  graph[VERTCOUNT][VERTCOUNT] {
  { 0, 2, 3, 0, 0, 0, 0 },
  { 2, 0, 3, 2, 1, 0, 0 },
  { 3, 3, 0, 0, 4, 0, 0 },
  { 0, 2, 0, 0, 3, 2, 0 },
  { 0, 1, 4, 3, 0, 0, 2 },
  { 0, 0, 0, 2, 0, 0, 0 },
  { 0, 0, 0, 0, 2, 0, 0 }
};

uint64_t heuristic[VERTCOUNT] { 8, 5, 6, 4, 2, 3, 0 };

std::deque<Vertex> edgesOf(Vertex vertex) {
  int *list = graph[vertex];
  std::deque<Vertex> result;

  for (uint32_t i = 0; i < VERTCOUNT; ++i) {
    if (list[i])
      result.push_back((Vertex)i);
  }
  return result;
}

Path astar(Vertex start, Vertex end) {
  std::deque<Path> possiblePaths { Path{{start}, 0 + heuristic[start]} };
  std::array<bool, VERTCOUNT> visited {};

  Path currPath;
  do {
    auto curr = std::min_element(possiblePaths.begin(), possiblePaths.end(), [](const Path &lhs, const Path &rhs) {
      return lhs.cost < rhs.cost;
    });
    currPath = *curr;
    possiblePaths.erase(curr);
    auto &endVertex = currPath.path.back();
    if (visited[endVertex])
      continue;
    visited[endVertex] = true;

    auto edges = edgesOf(endVertex);
    for (auto v : edges) {
      if (visited[v])
        continue;

      Path newPath = currPath;
      newPath.path.push_back(v);
      newPath.cost += graph[endVertex][v] - heuristic[endVertex] + heuristic[v] ;

      possiblePaths.push_back(newPath);
    }
  } while(currPath.path.back() != G);

  return currPath;
}

int main() {
  Path taken = astar(S, G);
  std::cout << "Actual Path\n";
  for(auto curr = taken.path.begin(); curr != taken.path.end() - 1; ++curr) 
    std::cout << VertexName(*curr) << " -> ";
  std::cout << VertexName(*(taken.path.end() - 1)) << "\n";
  std::cout << "Actual Path cost: " << taken.cost << std::endl;

  return EXIT_SUCCESS;
}