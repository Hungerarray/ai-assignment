#include "utility.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

using Path = std::vector<Edge>;

Vertex S{"S"};
Vertex A{"A"};
Vertex B{"B"};
Vertex C{"C"};
Vertex D{"D"};
Vertex G{"G"};

std::unordered_map<Vertex, uint32_t> heuristicCost{{S, 8}, {A, 5}, {B, 6},
                                                   {C, 3}, {D, 2}, {G, 0}};

Graph initGraph() {
  Graph graph;
  graph.addEdge(S, A, 2)
      .addEdge(S, B, 3)
      .addEdge(A, C, 2)
      .addEdge(A, B, 3)
      .addEdge(A, D, 1)
      .addEdge(B, D, 4)
      .addEdge(C, D, 4)
      .addEdge(C, G, 3)
      .addEdge(D, G, 2);

  return graph;
}

struct AstarInternal {
  Path path;
  uint64_t cost;

  AstarInternal(Path p, uint64_t c) : path{p}, cost{c} {}
  AstarInternal(const AstarInternal &other)
      : path{other.path}, cost{other.cost} {}
};

Path aStarSearch(const Graph &graph, const Vertex &start, const Vertex &goal) {
  std::vector<bool> visited(graph.totalVertex(), false);
  std::vector<AstarInternal> pathTable;
  Vertex curr = start;
  visited[graph[start]] = true;

  auto finished = [&visited]() {
    return std::all_of(visited.begin(), visited.end(),
                       [](bool value) { return value; });
  };

  auto pathCompare = [](const AstarInternal &lhs, const AstarInternal &rhs) {
    return lhs.cost < rhs.cost;
  };

  // seeding with inital paths
  std::vector<Edge> edges = graph.edgeStartVertex(curr);
  for (auto edge : edges) {
    pathTable.emplace_back(Path{edge},
                           edge.Cost + heuristicCost[graph[edge.End]]);
  }

  while (!finished()) {
    auto minPath =
        *std::min_element(pathTable.begin(), pathTable.end(), pathCompare);

    auto &currIndex = minPath.path.rbegin()->End;
    auto &currVertex = graph[currIndex];
    visited[currIndex] = true;

    if (currVertex == goal) {
      return minPath.path;
    }

    std::vector<Edge> edges = graph.edgeStartVertex(currVertex);
    for (auto edge : edges) {
      if (visited[edge.End])
        continue;

      AstarInternal newPath {minPath};
      newPath.path.push_back(edge);
      newPath.cost += edge.Cost + heuristicCost[graph[edge.End]] -
                               heuristicCost[currVertex];
      pathTable.push_back(newPath);
    }
    std::remove_if(pathTable.begin(), pathTable.end(),
                   [&visited](const AstarInternal &obj) {
                     return visited[obj.path.rbegin()->End];
                   });
  }

  VertexIndex goalIndex = graph[goal];
  auto possible = std::find_if(pathTable.begin(), pathTable.end(),
                               [goalIndex](const AstarInternal &obj) {
                                 return obj.path.rbegin()->End == goalIndex;
                               });
  return possible->path;
}

int main() {
  Graph graph = initGraph();
  auto tracePath = aStarSearch(graph, S, G);

  displayPath(graph, tracePath, "Trace Path:");
  uint64_t total = 0;
  for (auto edge : tracePath) {
    total += edge.Cost;
  }
  std::cout << "Path Cost: " << total << std::endl;

  return EXIT_SUCCESS;
}