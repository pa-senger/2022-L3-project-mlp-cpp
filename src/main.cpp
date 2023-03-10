#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include "../include/layer.hpp"
#include "../include/neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

int main() {

  // double (*pf_a)(double) = &sigma;
  // double (*pf_da)(double) = &dSigma;

  FeedForward<1, 1, 3> fw1;
  FeedForward<1, 1, 3> fw2(fw1);
  FeedForward<1, 1, 3> fw3;

  fw3 = fw1;

  return 0;
}
