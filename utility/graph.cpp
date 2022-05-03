#include "graph.h"
#include <algorithm>
#include <stdexcept>

VertexIndex Graph::addVertex(const Vertex &vertex) {
  m_vertexTable.push_back(vertex);
  return m_vertexTable.size() - 1;
}

Graph &Graph::addEdge(const Vertex &start, const Vertex &end, PathCost cost,
                      Edge::Direction direction) {
  auto startIndex = getIndex(start);
  auto endIndex = getIndex(end);
  if (!startIndex.has_value()) {
    startIndex = std::make_optional(addVertex(start));
  }
  if (!endIndex.has_value()) {
    endIndex = std::make_optional(addVertex(end));
  }

  m_edgeTable.emplace_back(startIndex.value(), endIndex.value(), cost,
                           direction);
  return *this;
}

size_t Graph::totalVertex() const { return m_vertexTable.size(); }

vector<Vertex> Graph::neighbour(const Vertex &vertex) const {
  auto edgeList = edgeStartVertex(vertex);

  vector<Vertex> vertexList;
  for (auto &edge : edgeList) {
    vertexList.push_back(m_vertexTable[edge.End]);
  }
  return vertexList;
}

vector<Edge> Graph::edgeStartVertex(const Vertex &vertex) const {
  auto vertexIndex = getIndex(vertex);
  if (!vertexIndex.has_value()) {
    throw std::out_of_range{"vertex doesnot exist in graph"};
  }

  vector<Edge> edgeList;
  for (auto &edge : m_edgeTable) {
    if (edge.Start == vertexIndex)
      edgeList.push_back(edge);
  }
  return edgeList;
}

vector<Edge> Graph::edgeEndVertex(const Vertex &vertex) const {
  auto vertexIndex = getIndex(vertex);
  if (!vertexIndex.has_value()) {
    throw std::out_of_range{"vertex doesnot exist in graph"};
  }

  vector<Edge> edgeList;
  for (auto &edge : m_edgeTable) {
    if (edge.End == vertexIndex)
      edgeList.push_back(edge);
  }
  return edgeList;
}

const Vertex &Graph::operator[](VertexIndex index) const {
  if (index >= m_vertexTable.size()) {
    throw std::out_of_range{"no vertex exist at given index"};
  }
  return m_vertexTable[index];
}

VertexIndex Graph::operator[](const Vertex &vertex) const {
  auto index = getIndex(vertex);

  if (!index.has_value()) {
    throw std::out_of_range{"vertex doesnot exist in graph"};
  }
  return index.value();
}

std::optional<VertexIndex> Graph::getIndex(const Vertex &vertex) const {
  auto iter = std::find(m_vertexTable.begin(), m_vertexTable.end(), vertex);
  return iter == m_vertexTable.end()
             ? std::nullopt
             : std::make_optional(iter - m_vertexTable.begin());
}

std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
  return os << vertex.Name;
}

bool operator==(const Edge &lhs, const Edge &rhs) {
  if (lhs.direction != rhs.direction)
    return false;

  if (lhs.direction == Edge::Direction::ONE)
    return (lhs.Start == rhs.Start) && (lhs.End == rhs.End);

  return ((lhs.Start == rhs.Start) && (lhs.End == rhs.End)) ||
         ((lhs.Start == rhs.End) && (lhs.End == rhs.Start));
}
