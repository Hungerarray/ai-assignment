#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using std::string;
using std::string_view;
using std::vector;

using VertexIndex = uint64_t;
using EdgeIndex = uint64_t;
using PathCost = uint64_t;

struct Vertex {
  string Name;

  Vertex(string_view name) : Name{name} {}

  bool operator==(const Vertex &next) const { return Name == next.Name; }
};

struct Edge {
  enum class Direction { ONE, TWO };
  VertexIndex Start;
  VertexIndex End;
  PathCost Cost;
  Direction direction;

  Edge(VertexIndex start, VertexIndex end, PathCost cost, Direction dir)
      : Start{start}, End{end}, Cost{cost}, direction{dir} {}
};

class Graph {
public:
  VertexIndex addVertex(const Vertex &vertex);
  Graph &addEdge(const Vertex &start, const Vertex &end, PathCost cost = 1,
                 Edge::Direction direction = Edge::Direction::TWO);

  size_t totalVertex() const;
  vector<Vertex> neighbour(const Vertex &vertex) const;
  vector<Edge> edgeStartVertex(const Vertex &vertex) const;
  vector<Edge> edgeEndVertex(const Vertex &vertex) const;
  const Vertex &operator[](VertexIndex index) const;
  VertexIndex operator[](const Vertex &vertex) const;

private:
  vector<Vertex> m_vertexTable;
  vector<Edge> m_edgeTable;

  std::optional<VertexIndex> getIndex(const Vertex &vertex) const;
};

std::ostream &operator<<(std::ostream &outputStream, const Vertex &vertex);
bool operator==(const Edge &lhs, const Edge &rhs);

namespace std {
template <> struct hash<Edge> {
  size_t operator()(const Edge &edge) const {
    constexpr size_t prime1 = 17, prime2 = 37;
    size_t hash = prime1;
    hash = hash * prime2 + std::hash<VertexIndex>{}(edge.Start);
    hash = hash * prime2 + std::hash<VertexIndex>{}(edge.End);
    return hash;
  }
};

template <> struct hash<Vertex> {
  size_t operator()(const Vertex &vertex) const {
    return std::hash<string>{}(vertex.Name);
  }
};
} // namespace std