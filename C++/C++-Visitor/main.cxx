#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

using namespace std::literals;

/*
 * Utility methods.
 */

// void seedRandomizer() {
//   srand(time(nullptr));
// }

// int generateRandomInteger(int minimum, int maximum) {
//   return rand() % (maximum - minimum) + minimum;
// }

std::string toLowercase(std::string text) {
  transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
  return text;
}

void toLowercaseInPlace(std::string& text) {
  transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
}

// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
std::string ltrim(const std::string& s, const std::string& characters) {
  auto start{s.find_first_not_of(characters)};
  return (start == std::string::npos) ? ""s : s.substr(start);
}

std::string rtrim(const std::string& s, const std::string& characters) {
  auto end{s.find_last_not_of(characters)};
  return (end == std::string::npos) ? ""s : s.substr(0, end + 1);
}

const std::string whitespace{" \n\r\t\f\v"s};
std::string trim(
  const std::string& s,
  const std::string& characters = whitespace
) {
  return rtrim(ltrim(s, characters), characters);
}

/*
 * Class definitions (i.e. HPP files).
 */

class EnemyVisitor;

class Enemy {
public:
  virtual int getPowerLevel() const = 0;
  virtual void accept(const EnemyVisitor& visitor) const = 0;
  virtual ~Enemy();
};

// For the following derived/child classes, the overridden methods could be
// marked as `final` instead of `override` since they're not intended to
// support further subclassing.
// See C.128 in the C++ Core Guidelines for recommended syntax:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final

class Spider : public Enemy {
public:
  int getPowerLevel() const override;
  void accept(const EnemyVisitor& visitor) const override;
  ~Spider();
private:
  int powerLevel{1u};
};

class Dragon : public Enemy {
public:
  int getPowerLevel() const override;
  void accept(const EnemyVisitor& visitor) const override;
  ~Dragon();
private:
  int powerLevel{100u};
};

class Spawner {
public:
  static std::unique_ptr<Enemy> spawnEnemy(const std::string& name);
};

class EnemyVisitor {
public:
  static void visit(const Spider* const spider);
  static void visit(const Dragon* const dragon);
};

/*
 * Class implementations (i.e. CPP files).
 */

std::unique_ptr<Enemy> Spawner::spawnEnemy(const std::string& name) {
  if (name == "spider"s) {
    return std::make_unique<Spider>();
  } else if (name == "dragon"s) {
    return std::make_unique<Dragon>();
  } else {
    // TODO: Use std::optional instead.
    return nullptr;
  }
}

Enemy::~Enemy() {
  std::cout << "Enemy has vanished.\n";
}

int Spider::getPowerLevel() const {
  return powerLevel;
}

void Spider::accept(const EnemyVisitor& visitor) const {
  visitor.visit(this);
}

Spider::~Spider() {
  std::cout << "The spider crawled into a hole.\n";
}

int Dragon::getPowerLevel() const {
  return powerLevel;
}

void Dragon::accept(const EnemyVisitor& visitor) const {
  visitor.visit(this);
}

Dragon::~Dragon() {
  std::cout << "The dragon flew away.\n";
}

void EnemyVisitor::visit(const Spider* const spider) {
  std::cout
    << "Eek! A spider! It has a power level of "
    << spider->getPowerLevel() << ".\n";
}

void EnemyVisitor::visit(const Dragon* const dragon) {
  std::cout
    << "Aargh! A dragon! It has a power level of "
    << dragon->getPowerLevel() << "!\n";
}

/*
 * Entry point.
 */

int main(int, char**) {
  // seedRandomizer();
  std::string input{""s};
  Spawner spawner{};
  EnemyVisitor visitor{};
  while (std::cout << "> ", getline(std::cin, input)) {
    input = toLowercase(trim(input));
    if (input == "exit"s) {
      break;
    } else if (input == "clear"s) {
      std::cout << "\x1b""c\x1b[3J";
      continue;
    } else if (input.empty()) {
      continue;
    }
    std::unique_ptr<Enemy> enemy{spawner.spawnEnemy(input)};
    if (!enemy) {
      std::cout << "I don't understand.\n";
      continue;
    }
    // This is where the individual class logic happens.
    // In other words, this is where a traditional "if/else" or "switch"
    // block would be for each class type.
    enemy->accept(visitor);
  }
  std::cout << "Bye.\n";
}
