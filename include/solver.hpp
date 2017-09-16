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
  bool done;
  bool stopped;

  thread* stopper;
  thread* checker;
  thread* func_f;
  thread* func_g;

  condition_variable cv;
  mutex m;

  void f(int x);
  void g(int x);
  void detachThreads();
  void waitForStop();
  void askUserToStop(int s);
  void action(bool &to, bool from, int time);

public:

  class Exception: public exception {
    string msg;
  public:
    virtual const char* what() const throw();
    explicit Exception(const char*  msg = "Unexpected error");
  };

  Solver();

  bool manager(int x);
};

#endif /* solver_h */
