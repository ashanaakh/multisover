#ifndef solver_h
#define solver_h

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

class Solver {

  bool fRes, gRes;
  bool stopped;
  bool notified;
  bool showPrompt;

  thread* checker;
  thread* func_f;
  thread* func_g;

  condition_variable cv;
  mutex m;
  mutex kekos;
  mutex safety;

  void f(int x);
  void g(int x);
  void detachThreads();
  void deleteThreads();
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
