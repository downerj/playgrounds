#include <string>

class Person {
public:
  Person(std::string firstName, std::string lastName):
    firstName(firstName), lastName(lastName) {}
  const std::string& getFirstName() const { return firstName; }
  const std::string& getLastName() const { return lastName; }
  std::string getFullName() const { return firstName + " " + lastName; }

  bool operator<(const Person& other) const;

  static bool CompareFirstLast(const Person& lhs, const Person& rhs);
  static bool CompareLastFirst(const Person& lhs, const Person& rhs);

  class FirstLastComparator {
  public:
    bool operator()(const Person& lhs, const Person& rhs);
  };

  class LastFirstComparator {
  public:
    bool operator()(const Person& lhs, const Person& rhs);
  };

private:
  std::string firstName;
  std::string lastName;
};

