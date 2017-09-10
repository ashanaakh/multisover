#include "solver.hpp"

const char* Solver::Exception::what() const throw() {
  return msg.c_str();
}

Solver::Exception::Exception(const char*  msg) : msg(msg) {}

void Solver::testFunc(func function) {
  function();

  done = true;
  cv.notify_one();
}

Solver::Solver(bool x) : res1(x), res2(x), done(false), stopped(false) {}

Solver::Solver(bool a, bool b) : res1(a), res2(b), done(false), stopped(false) {}

void Solver::waitForStop() {
  char answer;

  while (true) {
    answer = cin.get();
    if(answer == 'q') break;
  }

  stopped = true;
  cv.notify_all();
}

bool Solver::manager(int ftime, int gtime) {

  thread* first = new thread(&Solver::testFunc, this, [&] {
      this_thread::sleep_for(5s);
      });

  thread* second = new thread(&Solver::testFunc, this, [&] {
      this_thread::sleep_for(10s);
      });

  thread* stopper = new thread(&Solver::waitForStop, this);

  // thread* checker = new thread(&Solver::askUserToStop, this);

  unique_lock<mutex> lock(m);

  while(not done) {
    cv.wait(lock);

    if(stopped) {
      stopper->detach();
      first->detach();
      second->detach();

      delete first;
      delete second;
      delete stopper;

      throw Exception("Stopped by user");

    } else if(done) {

      if (not res1 || not res2) {
        first->detach();
        second->detach();
      } else {
        if (first->joinable()) first->join();
        if (second->joinable()) second->join();
      }

      delete first;
      delete second;

      return res1 && res2;
    }
  }

  throw Exception();
}
