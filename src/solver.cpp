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

void Solver::askUserToStop(int s) {
  char answer;

  while (true) {
    this_thread::sleep_for(chrono::seconds(s));
    cout << "Press y - to continue, q - to stop";
    answer = cin.get();
    if(answer == 'q') break;
  }

  stopped = true;
  cv.notify_all();
}

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
    this_thread::sleep_for(chrono::seconds(ftime));
  });

  thread* second = new thread(&Solver::testFunc, this, [&] {
    this_thread::sleep_for(chrono::seconds(gtime));
  });

  thread* stopper = new thread(&Solver::waitForStop, this);

  thread* checker = new thread(&Solver::askUserToStop, this, 5);

  unique_lock<mutex> lock(m);

  while(not done) {
    cv.wait(lock);

  if(stopped) {
    stopper->detach();
    checker->detach();
    first->detach();
    second->detach();

    delete first;
    delete second;
    delete stopper;
    delete checker;

    throw Exception("Stopped by user");

  } else if(done) {

    if (not res1 || not res2) {
      stopper->detach();
      checker->detach();
      first->detach();
      second->detach();
    } else {
      if (first->joinable()) first->join();
      if (second->joinable()) second->join();
    }

    delete first;
    delete second;
    delete stopper;
    delete checker;

    return res1 && res2;
    }
  }

  throw Exception();
}
