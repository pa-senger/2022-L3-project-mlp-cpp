#include "../include/activation_functions.hpp"
#include "../include/feed_forward.hpp"
#include "../include/layer.hpp"
#include "../include/mpc.hpp"
#include "../include/neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

// To compile use : cmake --preset debug (or release) /path_to_CMakeLists.txt

int main() {

  // double (*pf_a)(double) = &sigma;
  // double (*pf_da)(double) = &dSigma;

  neuron n1(4);

  n1.setWeightsRandom(0, 1);
  double X0[4]{1, 2, 1.1, 5};
  n1.activateNeuron(X0, 4);
  std::cout << n1 << std::endl;
  n1.setActivationFcts(sigma, dSigma, "sigmoid");
  n1.activateNeuron(X0, 4);
  std::cout << n1 << std::endl;

  layer l1(2, 5);

  std::cout << l1 << std::endl;

  FeedForward<3, 2, 4> fw3;

  int N[4]{1, 2, 3, 4};
  fw3.build(N, 4);
  double X[3]{1, 2, 3};
  fw3.evaluate(X, 3);
  // double *Y = fw3.getY();
  std::cout << fw3 << std::endl;

  mpc<3, 4, 4> m;

  m.build(N, 4);
  m.setAllWeightsRandoms(0, 1);
  m.setAllFct(sigma, dSigma, "sigmoid");
  m.evaluate(X, 3);
  // double *Y2 = m.getY();
  std::cout << m << std::endl;

  return 0;
}
