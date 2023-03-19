#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include <cassert>

int main() {

  FeedForward<0, 0, 0> fw;
  FeedForward<2, 3, 4> fw1;
  FeedForward<2, 3, 4> fw2(fw1);

  // (2 weights) * (3 neurons on the 1st layer)
  // then the remaning 4 layers still have 3 neurons but they take the output
  // of the first layer which is of size 3
  // 2*3 + 3*3 * 4 = 42
  assert(fw1.getTotalWeights() == 42);

  fw.unitTest();
  fw1.unitTest();
  fw2.unitTest();

  return 0;
}