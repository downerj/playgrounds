#include <iostream>

#include "intro.hpp"
#include "player.hpp"

using namespace std;

std::string promptName() {
  cout << "Please enter your name: ";
  std::string name;
  getline(cin, name);
  return name;
}

int main() {
  displayIntro();
  std::string name = promptName();
  Player player1(name);
  player1.sayHello();
  player1.printStats();
  player1.levelUp();

  cout << "Bye." << endl;
}
