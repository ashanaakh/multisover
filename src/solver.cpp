#include "solver.hpp"

const char* Solver::Exception::what() const throw() {
  return msg.c_str();
}

Solver::Exception::Exception(const char*  msg) : msg(msg) {}

void Solver::f(int x) {
  switch (x) {
    case 1: action(fRes, true, 1); break;
    case 2: action(fRes, true, 3); break;
    case 3: action(fRes, false, 3); break;
    case 4: action(fRes, true, 5); break;
    default: exit(1);
  }

  done = true;
  cv.notify_one();
}

void Solver::g(int x) {
  switch(x) {
    case 1: action(gRes, true, 3); break;
    case 2: action(gRes, true, 1); break;
    case 3: action(gRes, true, 4); break;
    case 4: action(gRes, false, 3); break;
    default: exit(1);
  }

  done = true;
  cv.notify_one();
}

// void Solver::testFunc(func function) {
//   function();
//   done = true;
//   cv.notify_one();
// }

Solver::Solver() : fRes(true), gRes(true), done(false),
  stopped(false) {}

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

void Solver::action(bool &to, bool from, int time) {
    this_thread::sleep_for(chrono::seconds(time));
    to = from;
}

void Solver::detachThreads() {
  stopper->detach();
  checker->detach();
  func_f->detach();
  func_g->detach();
}

bool Solver::manager(int x) {

  func_f = new thread(&Solver::f, this, x);
  func_g = new thread(&Solver::g, this, x);

  stopper = new thread(&Solver::waitForStop, this);
  checker = new thread(&Solver::askUserToStop, this, 10);

  unique_lock<mutex> lock(m);

  while(not done) {
    cv.wait(lock);

  if(stopped) {
    detachThreads();

    delete func_f;
    delete func_g;
    delete stopper;
    delete checker;

    throw Exception("Stopped by user");

  } else if(done) {

    if(not fRes || not gRes) {
      detachThreads();
    } else {
      if(func_f->joinable()) { func_f->join(); }
      if(func_g->joinable()) { func_g->join(); }
      stopper->detach();
      checker->detach();
    }

    delete func_f;
    delete func_g;
    delete stopper;
    delete checker;

    return fRes && gRes;
    }
  }

  throw Exception();
}
