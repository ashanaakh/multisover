#include <chrono>
#include <cassert>
#include <iostream>
#include <thread>
// #include <ncurses.h>

#include "solver.hpp"

using namespace std::chrono;
using std::cout;

void cancel() {
  this_thread::sleep_for(chrono::seconds(6));
}

void test1() {
  try {
    time_point<system_clock> start, end;
    Solver solver;

    thread stop(cancel);

    start = system_clock::now();
    bool result = solver.manager(6);
    end = system_clock::now();

    stop.join();

  } catch(exception& e) {
    cout << e.what() << endl;
  }
}

int main() {

  test1();

  return 0;
}
