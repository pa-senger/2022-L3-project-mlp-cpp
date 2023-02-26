#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"

int main() {

  FeedForward<2, 3, 4> fw;

  fw.unitTest();

  return 0;
}