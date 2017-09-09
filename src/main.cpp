#include "solver.h"

#include <string>

// operation &&

/*
 00 -> 0
 01 -> 0
 10 -> 0
 11 -> 1
 */

int main(int argc, char **argv) {

  Solver solver(1, 1);

  solver.manager();

  return 0;
}
