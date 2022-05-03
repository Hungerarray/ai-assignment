#include <iostream>
#include <functional>

void display(size_t hashValue) {
  std::cout << hashValue << std::endl;
}

int main () {
  std::vector<int> numbers { 1, 2, 3, 4, 5};
  for(auto curr = numbers.rbegin(); curr != numbers.rend(); curr++) {
    std::cout << *curr << '\t';
  }
  std::cout << std::endl;
  
  return EXIT_SUCCESS;
}