#ifndef solver_h
#define solver_h

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

#include <functional>

using namespace std;

class Solver {
  bool res1, res2, done, stopped;
  condition_variable cv;
  mutex m;

  using func = function<void()>;

  void testFunc(func f);
  void waitForStop();
  void askUserToStop(int s);

public:

  class Exception: public exception {
    string msg;
  public:
    virtual const char* what() const throw();

    Exception(const char*  msg = "Unexpected error");
  };

  Solver(bool x = false);
  Solver(bool a, bool b);

  bool manager(int ftime = 20, int gtime = 30);
};

#endif /* solver_h */
