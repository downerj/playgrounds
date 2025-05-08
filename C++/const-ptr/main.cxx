#include <algorithm>
#include <iostream>
#include <memory>

auto func1(int* a, int* b) -> void {
  *a = 5;
  *b = 10;
  std::swap(a, b);
}

auto func2(const int* a, const int* b) -> void {
  // *a = 5;
  std::swap(a, b);
}

auto func3(const int* const a, const int* const b) -> void {
  // *a = 5;
  // a = b;
}

auto main(int, char**) -> int {
  std::unique_ptr<int> val1{std::make_unique<int>(1)};
  std::unique_ptr<int> val2{std::make_unique<int>(2)};
  const std::unique_ptr<int> val3{std::make_unique<int>(3)};

  std::cout << *val1 << ' ' << *val2 << '\n';
  func1(val1.get(), val2.get());
  std::cout << *val1 << ' ' << *val2 << '\n';

  *val1 = 10;
  *val2 = 20;
  func2(val1.get(), val2.get());
  std::cout << *val1 << ' ' << *val2 << '\n';
}
