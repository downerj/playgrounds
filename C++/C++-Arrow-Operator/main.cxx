#include <iostream>
#include <string>

using namespace std;
using namespace std::literals;

class Hello {
public:
  Hello(const string& s) : s(s) {}
  auto toString() const -> const string& {
    return s;
  }
  auto operator->() const -> const Hello* {
    return this;
  }
private:
  const string s;
};

auto main(int, char**) -> int {
  const auto a = Hello{"Hello, there!"s};
  cout << a.toString() << endl;
  const auto b = Hello{"Bye."s};
  cout << b->toString() << endl;
}
