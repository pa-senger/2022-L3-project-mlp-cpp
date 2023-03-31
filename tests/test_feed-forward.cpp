#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include <cassert>

int main() {

  FeedForward<0, 0, 0> fw;
  FeedForward<2, 3, 4> fw1;
  FeedForward<2, 3, 4> fw2(fw1);

  // (2 weights) * (3 neurons on the 1st layer),
  // then the remaning 4 layers still have 3 neurons but they take the output
  // of the first layer which is of size 3,
  // 2*3 + 3*3 * 4 = 42
  assert(fw1.getTotalWeights() == 42);

  // Test evaluate:
  // Default weight = 1, activation fct = ReLU.
  // L0 :  <(1,2),(1,1)> = 3, 3 neurons -> Y = (3,3,3)
  // L1 : <(3,3,3),(1,1,1)> = 9, 3 neurons -> Y = (9,9,9)
  // L2 :  Y = (27,27,27)
  // L3 :  Y = (81,81,81)
  // L4 :  Y = (243,243,243)
  double X[3]{1, 2};
  double *Y = fw1.evaluate(X, 2);
  for (int i = 0; i < 3; ++i)
    assert(Y[i] == 243);

  // Test build:
  // L0 : <(1,2),(1,1)> = 3, 1 neuron -> Y = (3)
  // L1 : <3,1> = 3, 1 neuron -> Y = (3)
  // L2 : <3,1> = 3 , 2 neurons -> Y = (3,3)
  // L3 : <(3,3),(1,1)> = 6 , 3 neurons -> Y = (6,6,6)
  // L4 : <(6,6,6),(1,1,1)> = 18 , Y = (18,18,18)
  int N[4]{1, 1, 2, 3};
  fw2.build(N, 4);
  double *Y2 = fw2.evaluate(X, 2);
  for (int i = 0; i < 3; ++i)
    assert(Y2[i] == 18);

  fw.unitTest();
  fw1.unitTest();
  fw2.unitTest();

  return 0;
}