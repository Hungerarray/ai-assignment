#include "utility.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

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

std::vector<Edge> aStarSearch(const Graph &graph, const Vertex &start,
                               const Vertex &goal) {
  std::vector<bool> visited(graph.totalVertex(), false);
  std::vector<Edge> tracePath;
  Vertex curr = start;
  visited[graph[start]] = true;

  auto finished = [&visited]() {
    return std::all_of(visited.begin(), visited.end(),
                       [](bool value) { return value; });
  };

  auto greedyFunction = [](const std::vector<Vertex> &vs) {
    return *std::min_element(vs.begin(), vs.end(),
                     [](const Vertex &lhs, const Vertex &rhs) ->bool {
                       return heuristicCost[lhs] < heuristicCost[rhs];
                     });
  };

  while (!finished()) {
    auto neighbour = graph.neighbour(curr);
    Vertex next = greedyFunction(neighbour);
    VertexIndex nextIndex = graph[next];

    std::vector<Edge> edges = graph.edgeStartVertex(curr);
    Edge edge = *std::find_if(
        edges.begin(), edges.end(),
        [nextIndex](const Edge &edge) { return edge.End == nextIndex; });

    tracePath.push_back(edge);

    curr = next;
    if (curr == goal) {
      break;
    }
  }

  return tracePath;
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