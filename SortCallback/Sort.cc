#include <iostream>
// #include <list>
#include <set>
#include <string>

#include "Person.hh"

int main() {
  // std::list<Person> people = {
  std::set<Person, Person::FirstLastComparator> people = {
  // std::set<Person, Person::LastFirstComparator> people = {
    Person("James", "Downer"),
    Person("Emily", "Downer"),
    Person("Luke", "Downer"),
    Person("Adam", "Landon"),
    Person("Grace", "Landon"),
    Person("Adaline", "Landon"),
    Person("Kate", "Landon"),
    Person("Emily", "Landon"),
    Person("Spencer", "Hanson"),
    Person("Eric", "Hanson"),
    Person("Andrea", "Hanson"),
  };

  // people.sort();
  /*
  people.sort([](const Person& lhs, const Person& rhs) {
    return Person::CompareFirstLast(lhs, rhs);
    // return Person::CompareLastFirst(lhs, rhs);
  });
  */
  // people.sort(Person::CompareFirstLast);
  // people.sort(Person::CompareLastFirst);

  for (const auto& person : people) {
    std::cout << person.getFullName() << std::endl;
  }

  return EXIT_SUCCESS;
}

