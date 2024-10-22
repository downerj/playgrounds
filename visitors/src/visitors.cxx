#include <iostream>
#include <variant>

struct A {};
struct B {};
struct C {};

template<typename... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};

template<typename... Ts>
overload(Ts...) -> overload<Ts...>;

int main() {
  std::variant<A, B, C> item{C()};
  std::visit(overload{
    [](A&) { std::cout << "Hello, there!" << std::endl; },
    [](B&) { std::cout << "Blast! This is why I hate flying!" << std::endl; },
    [](C&) { std::cout << "Oh no, I'm not brave enough for politics." << std::endl; }
  }, item);
}
