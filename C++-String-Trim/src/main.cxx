#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

namespace my {

auto trim(std::string& str) -> std::string {
  const char* whitespace{" \n\r\t\f\v"};
  std::size_t start{str.find_first_not_of(whitespace)};
  std::size_t end{str.find_last_not_of(whitespace)};
  if (start == std::string::npos || end == std::string::npos) {
    return {};
  }
  return str.substr(start, end + 1 - start);
}

} // namespace my

auto main(int, char**) -> int {
  for (std::string s{}; std::getline(std::cin, s); s.clear()) {
    std::cout << my::trim(s) << '\n';
  }
}
