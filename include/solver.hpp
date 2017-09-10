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
  bool fRes, gRes;
  const bool fExpected, gExpected;
  bool done;
  bool stopped;

  thread* f;
  thread* g;
  thread* stopper;
  thread* checker;

  condition_variable cv;
  mutex m;

  using func = function<void()>;

  void detachThreads();
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

  Solver(bool a, bool b);

  bool manager(int ftime, int gtime);
};

#endif /* solver_h */
