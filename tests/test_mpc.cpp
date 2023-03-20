#include "../include/mpc.hpp"
#include <cassert>

int main() {

  mpc<0, 0, 0> m0;
  mpc<1, 1, 1> m1;
  mpc<2, 3, 4> m2;

  m0.unitTest();
  m1.unitTest();
  m2.unitTest();

  return 0;
}