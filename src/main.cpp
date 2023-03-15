#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include "../include/layer.hpp"
#include "../include/neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

// to compile use : cmake --preset debug (or release) /path_to_CMakeLists.txt

int main() {

  // double (*pf_a)(double) = &sigma;
  // double (*pf_da)(double) = &dSigma;

  FeedForward<3, 1, 3> fw1;
  FeedForward<3, 1, 3> fw2(fw1);
  FeedForward<3, 1, 3> fw3;

  fw3 = fw1;

  int w = fw3.getTotalWeights();
  std::cout << "w = " << w << std::endl;
  fw3.setAllWeightsDerivativesZeros();
  fw3.setAllWeightsRandoms(0, 1);
  fw3(2);

  // double W[];

  // fw3.setAllWeights(W, w);

  return 0;
}
