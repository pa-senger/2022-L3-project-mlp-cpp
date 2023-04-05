#include "../include/mpc.hpp"
#include <cassert>

int main() {

  // As mpc is a class template, most tests are written in the hpp.

  mpc<0, 0, 0> m0;
  mpc<1, 1, 1> m1;
  mpc<2, 3, 4> m2;

  int N[4]{1, 1, 2, 3};
  double X[3]{1, 2};

  // Test build:
  // Default weight = 1, activation fct = ReLU.
  // L0 : <(1,2),(1,1)> = 3, 1 neuron -> Y = (3)
  // L1 : <3,1> = 3, 1 neuron -> Y = (3)
  // L2 : <3,1> = 3 , 2 neurons -> Y = (3,3)
  // L3 : <(3,3),(1,1)> = 6 , 3 neurons -> Y = (6,6,6)
  // L4 : <(6,6,6),(1,1,1)> = 18 , Y = (18,18,18)

  m2.build(N, 4);
  double *Y2 = m2.evaluate(X, 2);
  for (int i = 0; i < 3; ++i)
    assert(Y2[i] == 18);

  m0.unitTest();
  m1.unitTest();
  m2.unitTest();

  return 0;
}