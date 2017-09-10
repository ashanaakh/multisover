#ifndef solver_h
#define solver_h

#include <iostream>
// #include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;
using namespace literals;

class Solver {

  using func = function<void()>;
  bool res1, res2, done;
  condition_variable cv;
  mutex m;

  void testFunc(func f);

public:

  Solver();
  Solver(bool a, bool b);

  void manager();
};

#endif /* solver_h */
