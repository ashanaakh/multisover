#include <chrono>
#include <cassert>
#include <iostream>

#include "solver.hpp"

using namespace std::chrono;
using std::cout;

void test1() {
  try {
    time_point<system_clock> start, end;

    Solver solver;

    start = system_clock::now();
    bool result = solver.manager(3);
    end = system_clock::now();

    assert(result == false);
    assert(duration_cast<seconds>(end - start).count() == 3);

  } catch(exception& e) {
    cout << e.what() << endl;
  }
}

int main() {

  test1();

  return 0;
}
