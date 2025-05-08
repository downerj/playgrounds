#include <iostream>
#include <string>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

/*
 * Terminal colors  
 */

namespace FGColors {
  const std::string BoldRed = "\e[1;31m";
  const std::string BoldGreen = "\e[1;32m";
  const std::string BoldYellow = "\e[1;33m";
  const std::string BoldBlue = "\e[1;34m";
  const std::string BoldMagenta = "\e[1;35m";
  const std::string BoldCyan = "\e[1;36m";
  const std::string BoldWhite = "\e[1;37m";
  const std::string BoldDefault = "\e[1;39m";
  const std::string Reset = "\e[0m";
}

namespace BGColors {
  const std::string BoldRed = "\e[1;41m";
  const std::string BoldGreen = "\e[1;42m";
  const std::string BoldYellow = "\e[1;43m";
  const std::string BoldBlue = "\e[1;44m";
  const std::string BoldMagenta = "\e[1;45m";
  const std::string BoldCyan = "\e[1;46m";
  const std::string BoldWhite = "\e[1;47m";
  const std::string BoldDefault = "\e[1;49m";
}

/*
 * Person
 */

class Person {
public:
  Person() = default;
  Person(const Person&) = delete;
  Person& operator=(const Person&) = delete;
  void* operator new(std::size_t) = delete;
  ~Person() = default;

  static const std::string GetName() {
    return BGColors::BoldYellow + "Person" + FGColors::Reset;
  }

  virtual const std::string getHello() const = 0;

  virtual const std::string getMessage() const {
    return Color + message + FGColors::Reset;
  }

  const std::string getGoodbye() const {
    return Color + goodbye + FGColors::Reset;
  }

private:
  static const std::string Color;
  const std::string message = "I have nothing else to say.";
  const std::string goodbye = "Goodbye.";
};
const std::string Person::Color = FGColors::BoldYellow;

/*
 * Jimmy
 */

class Jimmy : public Person {
public:
  Jimmy() = default;
  ~Jimmy() = default;

  static const std::string GetName() {
    return BGColors::BoldCyan + "Jimmy" + FGColors::Reset;
  }

  virtual const std::string getHello() const override final {
    return Color + hello + FGColors::Reset;
  }

  virtual const std::string getMessage() const override final {
    return Color + message + FGColors::Reset;
  }

  const std::string getGoodbye() const {
    return Color + goodbye + FGColors::Reset;
  }

private:
  static const std::string Color;
  const std::string hello = "Hello.";
  const std::string message = "What lovely weather we're having.";
  const std::string goodbye = "Take care now.";
};
const std::string Jimmy::Color = FGColors::BoldCyan;

/*
 * Start!
 */

int main(int, char**) {
  const Jimmy jimmy;
  const Person& person = jimmy;

  std::cout << Jimmy::GetName() << " is a "
    << Person::GetName() << "." << std::endl
    << std::endl;
  
  std::cout << Person::GetName()
    << " says:" << std::endl
    << "  " << person.getHello() << std::endl
    << "  " << person.getMessage() << std::endl
    << "  " << person.Person::getMessage() << std::endl
    << "  " << person.getGoodbye() << std::endl
    << std::endl;
  
  std::cout << Jimmy::GetName()
    << " says:" << std::endl
    << "  " << jimmy.getHello() << std::endl
    << "  " << jimmy.getMessage() << std::endl
    << "  " << jimmy.Person::getMessage() << std::endl
    << "  " << jimmy.getGoodbye() << std::endl
    << "  " << jimmy.Person::getGoodbye() << std::endl
    << std::endl;

  return EXIT_SUCCESS;
}
