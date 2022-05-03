#pragma once
#include "graph.h"
#include <string_view>
#include <vector>

std::vector<Edge> ComputeActualPath(const std::vector<Edge> &tracePath);

void displayPath(const Graph &graph, const std::vector<Edge> path,
                 std::string_view message);