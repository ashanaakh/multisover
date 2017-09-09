#include "solver.h"

using namespace literals;

void Solver::testfunc1(func function) {
  function();

  done = true;
  cv.notify_one();
}

Solver::Solver() : done(false), res2(true), res1(true) {}

Solver::Solver(bool a, bool b) : done(false), res2(b), res1(a) {}

void Solver::manager() {

  thread *first = new thread(&Solver::testfunc1, this, [&] {
    this_thread::sleep_for(1s);
  });

  thread *second = new thread(&Solver::testfunc1, this, [&] {
    this_thread::sleep_for(10s);
  });

  unique_lock<mutex> lock(m);

  while(!done) {
    cv.wait(lock);

    if(done) {
      if (!res1 || !res2) {
        first->detach();
        second->detach();
      } else {
        first->join();
        second->join();
      }

      delete first;
      delete second;

      cout << "result: " << (res1 && res2) << endl;

    }
  }
}
