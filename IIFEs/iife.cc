// Compile: make
// Run: ./iife

#include <iostream>
#include <string>

int main(int, char**) {
  std::string s("Bye.");
  std::cout << [] {
    std::string s("Hello!");
    return s;
  }() << std::endl;
  std::cout << s << std::endl;

  return EXIT_SUCCESS;
}
