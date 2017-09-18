#include <cstdlib>
#include <utility>
#include <string>
#include <exception>

#include "solver.hpp"

int main() {

  try {
    Solver solver;
    solver.manager(10);
  } catch(exception &e) {
    cout << e.what() << endl;
  }

  return 0;
}
