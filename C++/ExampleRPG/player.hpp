#include <string>

struct Player {
public:
  std::string name;
  unsigned int level;
  unsigned int health;
  unsigned int attack;
  unsigned int defense;
  unsigned int magick;

  Player();
  Player(const std::string& name);
  Player(const std::string& name, unsigned int level, unsigned int health, unsigned int attack, unsigned int defense, unsigned int magick);

  void sayHello();
  void printStats();
  void levelUp();

private:
  unsigned int getLevelUpValue();
};
