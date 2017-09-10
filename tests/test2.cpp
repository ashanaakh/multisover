#include <chrono>
#include <cassert>
#include <iostream>

#include "solver.hpp"

using namespace std::chrono;
using std::cout;

void test1() {
  time_point<system_clock> start, end;
  bool fRes = true, gRes = true;
  int fSec = 3, gSec = 1;

  Solver solver(fRes, gRes);

  try {
    start = system_clock::now();
    bool result = solver.manager(fSec, gSec);
    end = system_clock::now();

    assert(result);
    assert(duration_cast<seconds>(end - start).count() == fSec);

  } catch(exception& e) {
    cout << e.what() << endl;
  }
}

void test2() {
  time_point<system_clock> start, end;
  bool fRes = false, gRes = true;
  int fSec = 3, gSec = 2;

  Solver solver(fRes, gRes);

  try {
    start = system_clock::now();
    bool result = solver.manager(fSec, gSec);
    end = system_clock::now();

    assert(not result);
    assert(duration_cast<seconds>(end - start).count() == fSec);

  } catch(exception& e) {
    cout << e.what() << endl;
  }
}

int main() {

  test1();
  test2();

  return 0;
}
