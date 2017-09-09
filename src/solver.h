#ifndef solver_h
#define solver_h

#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <string>

using namespace std;

class Solver {

  using func = function<void()>;

  bool res1, res2;

  bool done;

  condition_variable cv;

  mutex m;

  void testfunc1(func f);

public:

  Solver();
  Solver(bool a, bool b);

  void manager();
};

#endif /* solver_h */
