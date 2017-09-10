#include <cstdlib>
#include <utility>
#include <string>
#include <exception>

#include "solver.hpp"

void showUsage() {
  cerr << "Usage --test <boolean> <boolean>, ";
  cerr << "boolean: 0 - false, 1 - true" << endl;
}

pair<int, int> cli(int count, char* argv[]) {
  if(count != 4 || string(argv[1]) != "--test") {
    showUsage();
    throw exception();

  } else {
    bool p1 = atoi(argv[2]);
    bool p2 = atoi(argv[3]);

    return pair<int, int>(p1, p2);
  }
}

int main(int argc, char* argv[]) {
  try {
    auto params = cli(argc, argv);
    Solver solver(params.first, params.second);
    solver.manager();
  } catch(exception& e) {
    e.what();
  }

  return 0;
}
