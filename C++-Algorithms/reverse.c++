#include <algorithm> // copy, reverse
#include <cstdlib> // EXIT_FAILURE
#include <iostream> // cerr, cout, endl
#include <string> // string
#include <vector> // vector

#include "vector_fn.h++"

using namespace std;

auto main(int argc, char** argv) -> int {
  auto args{vector<string>{argv, argv + argc}};
  args.erase(args.begin());
  if (args.size() == 0) {
    cerr << "List input cannot be empty" << endl;
    return EXIT_FAILURE;
  }
  reverse(args.begin(), args.end());
  cout << args << endl;
}
