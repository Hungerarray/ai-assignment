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

int  graph[VERTCOUNT][VERTCOUNT] =  {
  { 0, 2, 3, 0, 0, 0 },
  { 2, 0, 3, 2, 1, 0 },
  { 3, 3, 0, 0, 4, 0 },
  { 0, 2, 0, 0, 4, 3 },
  { 0, 1, 4, 4, 0, 2 },
  { 0, 0, 0, 3, 2, 0 }
};

std::deque<Vertex> edgesOf(Vertex vertex) {
  int *list = graph[vertex];
  std::deque<Vertex> result;

  for (uint32_t i = 0; i < VERTCOUNT; ++i) {
    if (list[i])
      result.push_back((Vertex)i);
  }
  return result;
}

Path bfs(Vertex start, Vertex end) {
  std::deque<Path> possiblePaths { Path{{S}, 0} };
  std::array<bool, VERTCOUNT> visited {};

  Path currPath;
  do {
    currPath = std::move(possiblePaths.front());
    possiblePaths.pop_front();
    auto &endVertex = currPath.path.back();
    if (visited[endVertex])
      continue;
    visited[endVertex] = true;

    auto edges = edgesOf(endVertex);
    std::sort(edges.begin(), edges.end(), [&endVertex](Vertex lhs, Vertex rhs){
      return graph[endVertex][lhs] < graph[endVertex][rhs];
    });

    for (auto v : edges) {
      if (visited[v])
        continue;

      Path newPath = currPath;
      newPath.path.push_back(v);
      newPath.cost += graph[endVertex][v];

      possiblePaths.push_back(newPath);
    }
  } while(currPath.path.back() != G);

  return currPath;
}

int main() {
  Path taken = bfs(S, G);
  std::cout << "Actual Path\n";
  for(auto curr = taken.path.begin(); curr != taken.path.end() - 1; ++curr) 
    std::cout << VertexName(*curr) << " -> ";
  std::cout << VertexName(*(taken.path.end() - 1)) << "\n";
  std::cout << "Actual Path cost: " << taken.cost << std::endl;

  return EXIT_SUCCESS;
}