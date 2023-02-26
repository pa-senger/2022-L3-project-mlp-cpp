#include "../include/activation_functions.hpp"
#include "../include/layer.hpp"

#include <cassert>
#include <iostream>

#define TOL 1e-6

double (*pf_a)(double) = &sigma;
double (*pf_da)(double) = &dSigma;

void layer::unitTest() {
  // test getters and setters
  layer la1;
  layer la2(2, 5);          // X=(x,y) , 5 neurons (0..4)
  la2.setWeight(1.1, 4, 1); // 4th neuron, 1st weight
  la2.setWeightDerivative(2.2, 0, 0);
  la2.setActivationFcts(pf_a, pf_da, 4);
  la2.setActivationFctName("sigma", 4);
  la2.setBiais(4.4, 0);
  la2.setDb(5.5, 4);
  assert(la2.getNbData() == 2);
  assert(la2.getNbNeurons() == 5);
  assert(la2.getWeight(4, 1) == 1.1);
  assert(la2.getWeightDerivative(0, 0) == 2.2);
  assert(la2.getBiais(0) == 4.4);
  assert(la2.getDb(4) == 5.5);

  layer la3(2, 3);
  la3.setWeight(0.1, 1, 1); // value, neuron , weight index
  la3.setWeight(0.2, 1, 1);
  la3.setBiais(0.3, 1); // value, neuron index in the layer
  la3.setActivationFcts(pf_a, pf_da, 1);
  assert(la3.arr_neurons_[1].getPo() - pf_a(0.8) < TOL);

  // default contructor
  layer c;
  assert(c.nb_neurons_ == 0);
  assert(c.nb_data_ == 0);
  assert(c.arr_neurons_ == nullptr);

  //  contructor taking size of data and nb of neuron
  layer c1(2, 5); // X=(x,y) , 5 neurons
  assert(c1.nb_data_ == 2);
  assert(c1.nb_neurons_ == 5);
  for (int i = 0; i < 4; ++i)
    assert(c1.arr_neurons_[i] == c1.arr_neurons_[i + 1]);

  //  copy constructor
  layer c2(c1);
  assert(c1.nb_neurons_ == c2.nb_neurons_);
  assert(c1.nb_data_ == c2.nb_data_);
  assert(c1.arr_neurons_ != c2.arr_neurons_);
  for (int i = 0; i < c1.nb_neurons_; ++i)
    assert(c1.arr_neurons_[i] == c2.arr_neurons_[i]);

  // affectation operator
  layer l1;
  layer l2(2, 3); // X=(x1, x2), 3 neurons
  layer l3(5, 0);
  l2.setBiais(1.1, 2);
  l2.setWeight(2.2, 2, 1);
  double X[3] = {1, 3, 5};
  l2.setActivationFcts(pf_a, pf_da, 2);
  l2.arr_neurons_[2].activateNeuron(X, 3);

  l1 = l2;

  assert(l1.getNbData() == l2.getNbData());
  assert(l1.getNbNeurons() == l2.getNbNeurons());

  // operator == is overloaded for neurons
  for (int i = 0; i < 2; ++i)
    assert(l1.arr_neurons_[i] == l2.arr_neurons_[i]);

  // test comparaison operator
  assert(l1 == l2);
  assert(!(l1 != l2));
  assert(l3 <= l1);
  assert(!(l1 <= l3));

  // test add weight
  layer l4(2, 3);
  l4.setWeightDerivative(1.1, 2, 0);
  l4.addWeightDerivative(0.3, 2, 0);
  assert(l4.getWeightDerivative(2, 0) - 1.4 < TOL);
  l4.addWeightDerivative(-1, 2, 0);
  assert(l4.getWeightDerivative(2, 0) - .4 < TOL);

  // test set all weights to one and weight's derivative to zero
  layer l5(5, 9);
  l5.setAllWeightsOnes();
  l5.setAllWeightsDerivativesZeros();
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 5; ++j) {
      assert(l5.getWeight(i, j) == 1);
      assert(l5.getWeightDerivative(i, j) == 0);
    }
  }

  // test set all weights to random
  layer la(5, 10);
  la.setAllWeightsRandoms(-1'000'000, 1'000'000);
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 4; ++j)
      assert(la.getWeight(i, j) != la.getWeight(i, j + 1));

  layer l6;
  l6.setAllWeightsOnes();
  l6.setAllWeightsDerivativesZeros();
  l6.setAllWeightsRandoms(-1'000'000, 1'000'000);
  layer l7(0, 0);
  l7.setAllWeightsOnes();
  l7.setAllWeightsDerivativesZeros();
  l7.setAllWeightsRandoms(-1'000'000, 1'000'000);

  // test  evaluate function
  l4.evaluateFct(3.1, 0); // layer has no neuron to evaluate, returns no errors
  l1.setActivationFcts(pf_a, pf_da, 2);

  assert(l1.evaluateFct(1.1, 2) == sigma(1.1));
  assert(l1.evaluateFctDerivative(2.5, 2) == dSigma(2.5));

  // test evaluate layer and the getter for Y
  layer l(2, 5);
  double X2[2]{1, 2};

  l.evaluateLayer(X2, 2); // X.(1,1) = 3, biais=0, heavyside(3 + biais) = 3
  double *Y = l.getY();

  for (int i = 0; i < 5; ++i)
    assert(Y[i] == 3);

  l.setActivationFcts(pf_a, pf_da, 4);
  l.setBiais(1.1, 0);
  l.setWeight(2.2, 4, 1);
  double *Y2 = l.evaluateLayer(X2, 2);

  std::cout << Y2[0] << std::endl;
  assert(Y2[0] == 4.1);
  assert(Y2[5] - sigma(5.4) < TOL);

  // test () overload
  assert(&l(4) == &l.arr_neurons_[4]);
  neuron nn(l(4));
  neuron nn2;
  nn2 = l(3);
}

int main() {

  layer::unitTest();

  return 0;
}