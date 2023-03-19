#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include <cassert>

int main() {

  FeedForward<0, 0, 0> fw;
  FeedForward<2, 3, 4> fw1;
  FeedForward<2, 3, 4> fw2(fw1);

  // (2 weights) * (3 neurons per layer) * (4 hidden layers + 1 outside layer)
  assert(fw1.getTotalWeights() == 2 * 3 * 5);

  fw.unitTest();
  fw1.unitTest();
  fw2.unitTest();

  return 0;
}