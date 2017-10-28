#include "solver.hpp"

const char* Solver::Exception::what() const throw() {
  return msg.c_str();
}

Solver::Exception::Exception(const char*  msg) : msg(msg) {}

Solver::Solver() : fRes(true), gRes(true), stopped(false), notified(false), showPrompt(true) {}

void Solver::f(int x) {
  switch(x) {
    case 1: action(fRes, true, 1); break;
    case 2: action(fRes, true, 3); break;
    case 3: action(fRes, false, 3); break;
    case 4: action(fRes, true, 5); break;
    case 5: action(fRes, true, 10); break;
    case 6: action(fRes, false, 6); break;
    default: action(fRes, true, 20); break;
  }

  {
    unique_lock<mutex> lock(safety);
    notified = true;
    cv.notify_one();
  }
}

void Solver::g(int x) {
  switch(x) {
    case 1: action(gRes, true, 3); break;
    case 2: action(gRes, true, 1); break;
    case 3: action(gRes, true, 4); break;
    case 4: action(gRes, false, 3); break;
    case 5: action(gRes, false, 8); break;
    case 6: action(gRes, true, 7); break;
    default: action(gRes, true, 30); break;
  }

  {
    unique_lock<mutex> lock(safety);
    notified = true;
    cv.notify_one();
  }
}

void Solver::askUserToStop(int s) {
  while(true) {
    if (showPrompt) {
      this_thread::sleep_for(chrono::seconds(s));
      cout << "q - stop, y - to continue without prompt, c - continue" << endl;
    }

    char answer;

    kekos.lock();
    answer = cin.get();

    if (answer == 'q') {
      kekos.unlock();
      unique_lock<mutex> lock(safety);
      notified = stopped = true;
      cv.notify_one();
      break;
    } else if (answer == 'y') {
      showPrompt = false;
      kekos.unlock();
      break;
    } else if (answer == 'c') {
      kekos.unlock();
    }
  }
}

void Solver::action(bool &to, bool from, int time) {
    this_thread::sleep_for(chrono::seconds(time));
    to = from;
}

void Solver::detachThreads() {
  checker->detach();
  func_f->detach();
  func_g->detach();
}

void Solver::deleteThreads() {
  delete checker;
  delete func_f;
  delete func_g;
}

bool Solver::manager(int x) {
  func_f = new thread(&Solver::f, this, x);
  func_g = new thread(&Solver::g, this, x);
  checker = new thread(&Solver::askUserToStop, this, 5);

  unique_lock<mutex> lock(m);

  while(true) {
    safety.lock();
    if (!notified) {
      safety.unlock();
      cv.wait(lock);

      if(notified) {

        if(stopped) {
          detachThreads();
          deleteThreads();
          throw Exception("Stopped by user");
        } else if(not fRes || not gRes) {
          kekos.lock();
          detachThreads();
          kekos.unlock();
        } else {

          func_f->join();
          func_g->join();

          kekos.lock();
          checker->detach();
          kekos.unlock();
        }

        deleteThreads();

        bool result = fRes && gRes;
        cout << boolalpha << result << endl;

        return result;
      }
    }
  }
  throw Exception();
}
