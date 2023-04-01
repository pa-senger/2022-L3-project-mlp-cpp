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

  std::cout << l1 << std::endl; // Not activated yet => Y = 0.

  FeedForward<3, 2, 4> fw3;

  int N[4]{1, 2, 3, 4};
  fw3.build(N, 4);
  double X[3]{1, 2, 3};
  fw3.evaluate(X, 3);
  std::cout << fw3 << std::endl;

  mpc<3, 4, 200> m;

  int N2[200];
  for (int i = 0; i < 200; ++i)
    N2[i] = i + 1;

  m.build(N2, 200);
  m.setAllWeightsRandoms(-1, 1);
  m.setAllFct(sigma, dSigma, "sigmoid");
  m.evaluate(X, 3);
  std::cout << m << std::endl;

  return 0;
}
