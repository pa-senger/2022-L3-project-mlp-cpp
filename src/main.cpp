#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include "../include/layer.hpp"
#include "../include/mpc.hpp"
#include "../include/neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

// to compile use : cmake --preset debug (or release) /path_to_CMakeLists.txt

int main() {

  // double (*pf_a)(double) = &sigma;
  // double (*pf_da)(double) = &dSigma;

  FeedForward<3, 2, 4> fw3;

  int X[4]{1, 2, 3, 4};
  fw3.build(X, 4);

  mpc<1, 2, 3> m;

  return 0;
}
