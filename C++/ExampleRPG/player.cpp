#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include "player.hpp"

using namespace std;

void toLowerCase(string& str) {
  transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) {
    return tolower(ch);
  });
}

// Default constructor.
// I set the attributes ("members") of the struct in the "initialization line", which is
// all the variables after the single colon (:).
Player::Player() : name("Nobody"), level(1), health(100), attack(1), defense(0), magick(0) {}

// Non-default constructor.
Player::Player(const std::string& name) : name(name), level(1), health(100), attack(1), defense(0), magick(0) {}

// Non-default constructor.
Player::Player(const std::string& name, unsigned int level, unsigned int health, unsigned int attack, unsigned int defense, unsigned int magick) :
  name(name),
  level(level),
  health(health),
  attack(attack),
  defense(defense),
  magick(magick) {}

void Player::sayHello() {
  cout << "Hello, " << name << "!" << endl;
}

void Player::printStats() {
  cout << "You are at level " << level << "." << endl;
  cout << "Your stats are:" << endl;
  cout << "- HP: " << health << endl;
  cout << "- ATK: " << attack << endl;
  cout << "- DEF: " << defense << endl;
  cout << "- MGK: " << magick << endl;
  cout << endl;
}

unsigned int Player::getLevelUpValue() {
  if (level < 4) {
    return 1;
  } else if (level < 7) {
    return 2;
  } else {
    return 3;
  }
}

void Player::levelUp() {
  // Base increase to all attributes.
  attack++;
  defense++;
  health++;
  magick++;
  cout << "All stats have been upgraded by 1." << endl;
  printStats();

  unsigned int value = getLevelUpValue();

  // Select which attribute to increase extra.
  for (int i = 1; i <= 3; i++) {
    cout << "Which stat to upgrade (" << i << "/3)? Upgrade value is " << value << "." << endl;
    string choice;
    do {
      cout << "> ";
      getline(cin, choice);
      toLowerCase(choice);
      if (choice == "") {
        continue;
      }
      if (choice == "atk") {
        attack += value;
        cout << "Attack is now " << attack << endl;
        printStats();
        break;
      } else if (choice == "def") {
        defense += value;
        cout << "Defense is now " << defense << endl;
        printStats();
        break;
      } else if (choice == "hp") {
        health += value;
        cout << "Health is now " << health << endl;
        printStats();
        break;
      } else if (choice == "mgk") {
        magick += value;
        cout << "Magick is now " << magick << endl;
        printStats();
        break;
      } else {
        cout << "Invalid choice \"" << choice << "\"!" << endl;
        continue;
      }
    } while (true);
  }
}
