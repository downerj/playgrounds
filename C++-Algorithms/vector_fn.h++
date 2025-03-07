#ifndef VECTOR_FN_HXX
#define VECTOR_FN_HXX

#include <iostream> // ostream
#include <iterator> // ostream_iterator
#include <vector> // vector

template <typename T>
auto operator<<(std::ostream& out, const std::vector<T>& container) -> std::ostream& {
  std::copy(container.cbegin(), container.cend(), std::ostream_iterator<T>{out, " "});
  return out;
}

#endif // VECTOR_FN_HXX
