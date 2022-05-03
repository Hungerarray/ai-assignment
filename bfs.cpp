#include "utility.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

Graph initGraph() {
  Vertex S{"S"};
  Vertex A{"A"};
  Vertex B{"B"};
  Vertex C{"C"};
  Vertex D{"D"};
  Vertex G{"G"};

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


std::vector<Edge> bfs(const Graph &graph, const Vertex &start, const Vertex &goal) {
  std::vector<bool> visited(graph.totalVertex(), false);
  std::queue<Edge> toVisit;
  std::vector<Edge> tracePath;

  auto pathCompare = [](const Edge &lhs, const Edge &rhs) {
    return lhs.Cost < rhs.Cost;
  };

  auto hasVisited = [&visited](const VertexIndex &index) {
    return visited[index];
  };

  visited[graph[start]] = true;
  auto edges = graph.edgeStartVertex(start);
  std::sort(edges.begin(), edges.end(), pathCompare);
  for (auto &edge : edges) {
    toVisit.push(edge);
  }

  while (!toVisit.empty()) {
    // get current edge, skip if already visited
    auto currEdge = toVisit.front();
    toVisit.pop();
    if (hasVisited(currEdge.End)) {
      continue;
    }
    // add current edge to tracePath
    // and mark current edge as visited
    tracePath.push_back(currEdge);
    visited[currEdge.End] = true;

    // stop if goal reached
    if (graph[currEdge.End] == goal) {
      break;
    }

    // get the edges that start from the end of current edge
    // and add them if not already visited
    edges = graph.edgeStartVertex(graph[currEdge.End]);
    std::sort(edges.begin(), edges.end(), pathCompare);
    for (auto edge : edges) {
      if (!hasVisited(edge.End))
        toVisit.push(edge);
    }
  }
  return tracePath;
}

int main() {
  Graph graph = initGraph();
  Vertex start{"S"}, goal{"G"};
  auto tracePath = bfs(graph, start, goal);
  displayPath(graph, tracePath, "Trace Path:");
  std::cout << std::endl;

  auto actualPath = ComputeActualPath(tracePath);
  PathCost total = 0;
  for (auto &edge : actualPath) {
    total += edge.Cost;
  }
  displayPath(graph, actualPath, "Actual Path:");
  std::cout << "Actual Path Cost: " << total << std::endl;

  return EXIT_SUCCESS;
}