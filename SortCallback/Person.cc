#include "Person.hh"

bool Person::operator<(const Person& other) const {
  // return Person::CompareFirstLast(*this, other);
  
  if (firstName == other.firstName) {
    return lastName < other.lastName;
  }
  return firstName < other.firstName;
  
  /*
  if (lastName == rhs.lastName) {
    return firstName < rhs.firstName;
  }
  return lastName < rhs.lastName;
  */
}

bool Person::CompareFirstLast(const Person& lhs, const Person& rhs) {
  if (lhs.getFirstName() == rhs.getFirstName()) {
    return lhs.getLastName() < rhs.getLastName();
  }
  return lhs.getFirstName() < rhs.getFirstName();
}

bool Person::CompareLastFirst(const Person& lhs, const Person& rhs) {
  if (lhs.getLastName() == rhs.getLastName()) {
    return lhs.getFirstName() < rhs.getFirstName();
  }
  return lhs.getLastName() < rhs.getLastName();
}

bool Person::FirstLastComparator::operator()(
    const Person& lhs, const Person& rhs) {
  return Person::CompareFirstLast(lhs, rhs);
}

bool Person::LastFirstComparator::operator()(
    const Person& lhs, const Person& rhs) {
  return Person::CompareLastFirst(lhs, rhs);
}

