#include "../include/activation_functions.hpp"
#include "../include/layer.hpp"
#include <iostream>

#define TOL 1e-6

double (*pf_a)(double) = &sigma;
double (*pf_da)(double) = &dSigma;

int layer::unitTest1() {
  int passed = 0;

  // default contructor
  layer c;
  if (c.nb_neurons_ == 0 && c.nb_data_ == 0 && c.arr_neurons_ == nullptr)
    ++passed;
  // passed = 1

  //  contructor taking size of data and nb of neuron
  layer c1(2, 5); // X=(x,y) , 5 neurons
  if (c1.nb_data_ == 2 && c1.nb_neurons_ == 5)
    ++passed;
  // passed = 2
  int k = 0;
  for (int i = 0; i < 4; ++i) {
    if (c1.arr_neurons_[i] == c1.arr_neurons_[i + 1])
      ++k;
  }
  if (k % 4 == 0)
    ++passed;
  // passed = 3

  //  copy constructor
  layer c2(c1);
  if (c1.nb_neurons_ == c2.nb_neurons_ && c1.nb_data_ == c2.nb_data_ &&
      c1.arr_neurons_ !=
          c2.arr_neurons_) // last checks if pointers arent the same
    ++passed;
  // passed = 4
  k = 0;
  for (int i = 0; i < c1.nb_neurons_; ++i) {
    if (c1.arr_neurons_[i] == c2.arr_neurons_[i])
      ++k;
  }
  if (k % c1.nb_neurons_ == 0)
    ++passed;
  // passed = 5

  return passed % 5;
}

int layer::unitTest2() { // tests getters setters
  int passed = 0;

  layer l1;
  layer l2(2, 5); // X=(x,y) , 5 neurons (0..4)
  layer l3(2, 3);
  l2.setWeight(1.1, 4, 1); // 4th neuron, 1st Weighteight
  l2.setWeightDerivative(2.2, 0, 0);
  l2.setActivationFcts(pf_a, pf_da, 4);
  l2.setActivationFctName("sigma", 4);
  l2.setBiais(4.4, 0);
  l2.setDb(5.5, 4);
  if (l2.getNbData() == 2 && l2.getNbNeurons() == 5 &&
      l2.getWeight(4, 1) == 1.1 && l2.getWeightDerivative(0, 0) == 2.2 &&
      l2.getBiais(0) == 4.4 && l2.getDb(4) == 5.5)
    ++passed;
  // passed = 1;
  l3.setWeight(0.1, 1, 1); // value, neuron , Weight index
  l3.setWeight(0.2, 1, 1);
  l3.setBiais(0.3, 1); // value, neuron index in the layer
  l3.setActivationFcts(pf_a, pf_da, 1);
  double X[2] = {1, 2};
  l3.arr_neurons_[1].activateNeuron(X, 2);
  if (l3.arr_neurons_[1].getPo() == pf_a(0.8))
    ++passed;
  // passed = 2

  return passed % 2;
}

int layer::unitTest3() { // tests operators
  int passed = 0;

  layer l1;
  layer l2(2, 3); // X=(x1, x2), 3 neurons
  layer l3(5, 0);
  l2.setBiais(1.1, 2);
  l2.setWeight(2.2, 2, 1);
  double X[3] = {1, 3, 5};
  l2.setActivationFcts(pf_a, pf_da, 2);
  l2.arr_neurons_[2].activateNeuron(X, 3);

  l1 = l2;

  if (l1.getNbData() == l2.getNbData() &&
      l1.getNbNeurons() == l2.getNbNeurons())
    ++passed;
  // passed = 1
  int k = 0;
  for (int i = 0; i < 2; ++i) {
    if (l1.arr_neurons_[i] ==
        l2.arr_neurons_[i]) // operator == if overloaded for neurons
      ++k;
  }
  if (k % 2 == 0)
    ++passed;
  // passed = 2
  if (l1 == l2)
    ++passed;
  // passed = 3
  if (!(l1 != l2))
    ++passed;
  // passed = 4
  if (l3 <= l1)
    ++passed;
  // passed = 5
  if (!(l1 <= l3))
    ++passed;
  // passed = 6

  return passed % 6;
}

int layer::unitTest4() {
  int passed = 0;

  layer l1(2, 3);
  l1.setWeightDerivative(1.1, 2, 0);
  l1.addWeightDerivative(0.3, 2, 0);

  if (l1.getWeightDerivative(2, 0) - 1.4 < TOL)
    ++passed;
  // passed = 1
  l1.addWeightDerivative(-1, 2, 0);

  if (l1.getWeightDerivative(2, 0) - .4 < TOL)
    ++passed;

  // passed = 2
  layer l2(5, 9);
  l2.setAllWeightsOnes();
  l2.setAllWeightsDerivativesZeros();
  int k = 0;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (l2.getWeight(i, j) == 1 && l2.getWeightDerivative(i, j) == 0)
        ++k;
    }
  }
  if (k % 45 == 0)
    ++passed;
  // passed = 3

  l2.setAllWeightsRandoms();
  k = 0;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (l2.getWeight(i, j) != l2.getWeight(i, j + 1))
        ++k;
    }
  }
  if (k % 36 == 0)
    ++passed;
  // passed = 4

  layer l3;
  l3.setAllWeightsOnes();
  l3.setAllWeightsDerivativesZeros();
  l3.setAllWeightsRandoms();
  layer l4(0, 0);
  l4.setAllWeightsOnes();
  l4.setAllWeightsDerivativesZeros();
  l4.setAllWeightsRandoms();

  l4.evaluateFct(3.1, 0); // layer has no neuron to evaluate, returns no errors
  l1.setActivationFcts(pf_a, pf_da, 2);

  if (l1.evaluateFct(1.1, 2) == sigma(1.1) &&
      l1.evaluateFctDerivative(2.5, 2) == dSigma(2.5))
    ++passed;
  // passed = 5

  layer l(2, 5);
  double X[2]{1, 2};

  l.evaluateLayer(X, 2); // X.(1,1) = 3, biais=0, heavyside(3 + biais) = 3
  double *Y = l.getY();
  k = 0;
  for (int i = 0; i < 5; ++i) {
    if (Y[i] == 3)
      ++k;
  }
  if (k % 5 == 0)
    ++passed;
  // passed =6

  l.setActivationFcts(pf_a, pf_da, 4);
  l.setBiais(1.1, 0);
  l.setWeight(2.2, 4, 1);
  l.evaluateLayer(X, 2);

  double *Y2 = l.getY();
  if (Y2[0] == 4.1 && (Y2[5] - sigma(5.4) < TOL))
    ++passed;
  // passed = 7

  if (&l(4) == &l.arr_neurons_[4])
    ++passed;

  neuron nn(l(4));
  neuron nn2;
  nn2 = l(3);
  // passed = 8

  return passed % 8;
}

int main() {

  return (layer::unitTest1() + layer::unitTest2() + layer::unitTest3() +
          layer::unitTest4());
}