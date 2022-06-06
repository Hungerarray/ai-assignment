// WAP to implement given production value to sort given alphabet
// Production Rule;
//    1: ba -> ab
//    2: ca -> ac
//    3: cb -> bc
// String: cbacba

#include <iostream>
#include <string>

using std::string;

// Rules:
// 1: ba -> ab
// 2: ca -> ac
// 3: cb -> bc
enum class Rules { RULE1, RULE2, RULE3, NORULE };

// loop: start
// read the string

// figure out the rules to be used
Rules RuleChoice(const string &str) {
  char prev = str[0];
  char curr = str[1];

  for (size_t i = 1; i < str.length(); curr = str[i++]) {
    if (prev == 'b' && curr == 'a')
      return Rules::RULE1;
    if (prev == 'c' && curr == 'a')
      return Rules::RULE2;
    if (prev == 'c' && curr == 'b')
      return Rules::RULE3;
    
    prev = curr;
  }
  return Rules::NORULE;
}

// apply the rules on the string
void ApplyRule(Rules rule, string &str) {
  for (size_t i = 1; i < str.length(); ++i) {
    char &prev = str[i - 1];
    char &curr = str[i];

    switch (rule) {
    case Rules::RULE1:
      if (prev == 'b' && curr == 'a')
        std::swap(prev, curr);
      break;

    case Rules::RULE2:
      if (prev == 'c' && curr == 'a')
        std::swap(prev, curr);
      break;

    case Rules::RULE3:
      if (prev == 'c' && curr == 'b')
        std::swap(prev, curr);
      break;

    case Rules::NORULE:
    default:
      break;
    }
  }
}

// goto: start if the string is not sorted

int main() {
  string str = "cbacba";
  std::cout << "Initial String: " << str << std::endl;

  Rules curr;
  while ((curr = RuleChoice(str)) != Rules::NORULE) {
    ApplyRule(curr, str);
    std::cout << "Current String: " << str << std::endl;
  }

  std::cout << "Final String: " << str << std::endl;
  return EXIT_SUCCESS;
}