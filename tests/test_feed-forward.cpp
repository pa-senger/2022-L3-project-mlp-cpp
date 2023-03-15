#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"

int main() {

  FeedForward<0, 0, 0> fw;
  FeedForward<2, 3, 4> fw1;
  FeedForward<2, 3, 4> fw2(fw1);

  fw.unitTest();
  fw1.unitTest();
  fw2.unitTest();

  return 0;
}