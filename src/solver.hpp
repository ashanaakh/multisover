#ifndef solver_h
#define solver_h

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <string>

using namespace std;
using namespace literals;

class Solver {
  bool res1, res2, done, stopped;
  condition_variable cv;
  mutex m;

  using func = function<void()>;

  void testFunc(func f);
  void waitForStop();

public:

  class Exception: public exception {
    string msg;
  public:
    virtual const char* what() const throw();

    Exception(const char*  msg = "Unexpected error");
  };

  Solver(bool x = false);
  Solver(bool a, bool b);

  bool manager(int ftime = 5, int gtime = 10);
};

#endif /* solver_h */
