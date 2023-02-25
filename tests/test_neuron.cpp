#include "../include/activation_functions.hpp"
#include "../include/neuron.hpp"
#include <cassert>
#include <cmath>
#define TOL 1e-6

double (*pf_s)(double) = &sigma;
double (*pf_ds)(double) = &dSigma;

int neuron::unitTest0() { // tests getters setters
  int passed = 0;

  neuron n(3);
  n.setWeight(1.1, 0);
  n.setWeightDerivative(2.2, 0);
  n.setBiais(3.3);
  n.setDb(4.4);
  n.setActivationFcts(pf_s, pf_ds);

  if (n.getWeight(0) == 1.1 && n.getWeightDerivative(0) == 2.2 &&
      n.getBiais() == 3.3 && n.getDb() == 4.4 && n.getPo() == 0. &&
      n.getSizeX() == 3)
    ++passed;
  // passed = 1;
  if (n.pf_activation_ == pf_s)
    ++passed;
  // passed = 2
  if (n.pf_activation_(2.2) - pf_s(2.2) <= TOL) // sigma(2.2) ~= 0.90024
    ++passed;
  // passed = 3
  if (n.pf_activation_d_ == pf_ds)
    ++passed;
  // passed = 4
  if (n.pf_activation_d_(2.2) - pf_ds(2.2) <= TOL) // dSigma(2.2) ~= 0.109459
    ++passed;
  // passed = 5

  return passed % 5;
}

int neuron::unitTest() {

  int k = 0;

  // test default constructor
  neuron n1;
  assert(n1.getSizeX() == 1);
  assert(n1.getWeight(0) == 1);
  assert(n1.getBiais() == 0);
  assert(n1.getDb() == 0);
  assert(n1.getPo() == 0);
  assert(n1.getPe() == 0);
  if (n1.pf_activation_ == &ReLU && n1.pf_activation_d_ == &dReLU)
    ++k;
  // k = 1

  // test construtor taking the size of the entry vector
  neuron n2(3);
  assert(n2.getSizeX() == 3);
  assert(n2.getWeight(0) == 1);
  assert(n2.getWeight(1) == 1);
  assert(n2.getWeight(2) == 1);
  assert(n2.getBiais() == 0);
  assert(n2.getDb() == 0);
  assert(n2.getPo() == 0);
  assert(n2.getPe() == 0);
  if (n2.pf_activation_ == &ReLU && n2.pf_activation_d_ == &dReLU)
    ++k;
  // k = 2

  // test constructor with activation functions
  neuron n3(2, &sigma, &dSigma, "sigmoid");
  assert(n3.getSizeX() == 2);
  assert(n3.getWeight(0) == 1);
  assert(n3.getWeight(1) == 1);
  assert(n3.getBiais() == 0);
  assert(n3.getDb() == 0);
  assert(n3.getPo() == 0);
  assert(n3.getPe() == 0);
  if (n3.pf_activation_ == &sigma && n3.pf_activation_d_ == &dSigma)
    ++k;
  // k =3

  // tests setters
  n2.setBiais(1);
  n2.setDb(2);
  n2.setWeight(3, 0);
  n2.setWeightDerivative(4, 1);
  assert(n2.getBiais() == 1);
  assert(n2.getDb() == 2);
  assert(n2.getWeight(0) == 3);
  assert(n2.getWeight(1) == 1);
  assert(n2.getWeight(2) == 1);
  assert(n2.getWeightDerivative(0) == 0);
  assert(n2.getWeightDerivative(1) == 4);
  assert(n2.getWeightDerivative(2) == 0);

  // test copy constructor
  neuron n4(n2);
  assert(n4.getSizeX() == 3);
  assert(n4.getBiais() == 1);
  assert(n4.getDb() == 2);
  assert(n4.getWeight(0) == 3);
  assert(n4.getWeight(1) == 1);
  assert(n4.getWeight(2) == 1);
  assert(n4.Weight_ != n2.Weight_); // test memory allocation of the arrays
  assert(n4.Weight_d_ != n2.Weight_d_);
  assert(n4.getWeightDerivative(0) == 0);
  assert(n4.getWeightDerivative(1) == 4);
  assert(n4.getWeightDerivative(2) == 0);
  assert(n4.getPo() == 0);
  assert(n4.getPe() == 0);
  if (n4.pf_activation_ == n2.pf_activation_ &&
      n4.pf_activation_d_ == n2.pf_activation_d_)
    ++k;
  // k = 4

  // test assigment operator
  n1 = n4; // n1 was the default neuron
  assert(n1.getSizeX() == 3);
  assert(n2.getBiais() == 1);
  assert(n1.getDb() == 2);
  assert(n1.getWeight(0) == 3);
  assert(n1.getWeight(1) == 1);
  assert(n1.getWeight(2) == 1);
  assert(n4.Weight_ != n1.Weight_);
  assert(n4.Weight_d_ != n1.Weight_d_);
  assert(n1.getWeightDerivative(0) == 0);
  assert(n1.getWeightDerivative(1) == 4);
  assert(n1.getWeightDerivative(2) == 0);
  assert(n1.getPo() == 0);
  assert(n1.getPe() == 0);
  if (n4.pf_activation_ == n1.pf_activation_ &&
      n4.pf_activation_d_ == n1.pf_activation_d_)
    ++k;
  // k = 5

  // test weight setters
  n1.setWeightsOnes();
  assert(n1.getWeight(0) == 1);
  assert(n1.getWeight(1) == 1);
  assert(n1.getWeight(2) == 1);

  n1.setWeightsDerivativesZeros();
  assert(n1.getWeightDerivative(0) == 0);
  assert(n1.getWeightDerivative(1) == 0);
  assert(n1.getWeightDerivative(2) == 0);

  n1.setWeightsRandom();
  assert(n1.getWeight(0) != n1.getWeight(1));
  assert(n1.getWeight(0) != n1.getWeight(2));
  assert(n1.getWeight(1) != n1.getWeight(2));

  // test activate
  neuron n5(4);
  for (int i = 0; i < 4; ++i) {
    n5.setWeight(i + 1, i);
  }
  double X[4] = {.1, .2, .3, .4};
  n5.setBiais(.2);
  n5.setActivationFcts(pf_s, pf_ds);
  n5.activateNeuron(X, 4);
  assert(n5.getPe() == 3.2);
  assert(n5.getPo() == sigma(3.2));

  return (k % 5);
}

int main() { return (neuron::unitTest0() + neuron::unitTest()); }