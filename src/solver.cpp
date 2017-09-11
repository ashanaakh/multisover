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

Solver::Solver(bool a, bool b) : fRes(true), gRes(true), done(false),
  stopped(false), fExpected(a), gExpected(b) {}

void Solver::askUserToStop(int s) {
  while(true) {
    char answer;

    this_thread::sleep_for(chrono::seconds(s));
    cout << "Press y - to continue, q - to stop" << endl;
    answer = cin.get();
    if(answer == 'q') { break; }
  }

  stopped = true;
  cv.notify_all();
}

void Solver::waitForStop() {
  char answer;

  while(true) {
    answer = cin.get();
    if(answer == 'q') break;
  }

  stopped = true;
  cv.notify_all();
}

void Solver::detachThreads() {
  stopper->detach();
  checker->detach();
  f->detach();
  g->detach();
}

bool Solver::manager(int ftime, int gtime) {
  f = new thread(&Solver::testFunc, this, [&] {
    this_thread::sleep_for(chrono::seconds(ftime));
    fRes = fExpected;
  });

  g = new thread(&Solver::testFunc, this, [&] {
    this_thread::sleep_for(chrono::seconds(gtime));
    gRes = gExpected;
  });

  stopper = new thread(&Solver::waitForStop, this);
  checker = new thread(&Solver::askUserToStop, this, 10);

  unique_lock<mutex> lock(m);

  while(not done) {
    cv.wait(lock);

  if(stopped) {
    detachThreads();

    delete f;
    delete g;
    delete stopper;
    delete checker;

    throw Exception("Stopped by user");

  } else if(done) {

    if(not fRes || not gRes) {
      detachThreads();
    } else {
      if(f->joinable()) { f->join(); }
      if(g->joinable()) { g->join(); }
      stopper->detach();
      checker->detach();
    }

    delete f;
    delete g;
    delete stopper;
    delete checker;

    return fRes && gRes;
    }
  }

  throw Exception();
}
