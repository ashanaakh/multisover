#include "solver.hpp"

void Solver::testFunc(func function) {
  function();

  done = true;
  cv.notify_one();
}

Solver::Solver() : done(false), res2(true), res1(true) {}

Solver::Solver(bool a, bool b) : done(false), res2(b), res1(a) {}

void Solver::manager() {

  thread* first = new thread(&Solver::testFunc, this, [&] {
    this_thread::sleep_for(1s);
  });

  thread* second = new thread(&Solver::testFunc, this, [&] {
    this_thread::sleep_for(10s);
  });

  unique_lock<mutex> lock(m);

  while(not done) {
    cv.wait(lock);

    if(done) {
      if (not res1 || not res2) {
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
