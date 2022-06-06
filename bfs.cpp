#include <iostream>
#include <vector>

constexpr uint32_t VERTCOUNT = 6;
enum Vertex { S, A, B, C, D, G };

int  graph[VERTCOUNT][VERTCOUNT] =  {
  { 0, 2, 3, 0, 0, 0 },
  { 2, 0, 3, 2, 1, 0 },
  { 3, 3, 0, 0, 4, 0 },
  { 0, 2, 0, 0, 4, 3 },
  { 0, 1, 4, 4, 0, 2 },
  { 0, 0, 0, 3, 2, 0 }
};

std::vector<Vertex> edgesOf(Vertex vertex) {
  int *list = graph[vertex];
  std::vector<Vertex> result;

  for (uint32_t i = 0; i < VERTCOUNT; ++i) {
    if (list[i])
      result.push_back((Vertex)i);
  }
  return result;
}



int main() {
  auto edges = edgesOf(S);
  for (auto e : edges) 
    std::cout << e << " ";
  std::cout << std::endl; 

  return EXIT_SUCCESS;
}