#ifndef MPC_HPP
#define MPC_HPP
#include "activation_functions.hpp"
#include "feed_forward.hpp"
#include <cassert>
#include <cstddef>

template <int n_in, int n_out, int n_layer>
class mpc : public FeedForward<n_in, n_out, n_layer> {
public:
  // * Constructors && Destructor using parent's one
  // Parent default contructor will be used by default if not specified.
  mpc() {}
  mpc(const mpc &m) : FeedForward<n_in, n_out, n_layer>(m) {}
  ~mpc() {}

  // * Methods
  // This method sets the activation fct for all the layer in the network.
  void setAllFct(double (*pf_a)(double), double (*pf_da)(double),
                 std::string name = "n/a");
  // This method sets the activation for a single layer.
  void setFct(double (*pf_a)(double), double (*pf_da)(double), int i_layer,
              std::string name = "n/a");
  // This method build the neural network using an array containing the
  // number of neurons on each hidden layer as a param
  void build(int *Nb_Neurons, int size);

  // * Tests
  static void unitTest();

private:
};

// ! Definitions

template <int n_in, int n_out, int n_layer>
void mpc<n_in, n_out, n_layer>::setAllFct(double (*pf_a)(double),
                                          double (*pf_da)(double),
                                          std::string name) {
  for (int i = 0; i < n_layer + 1; ++i) {
    for (std::size_t j = 0; j < this->L_[i].getNbNeurons(); ++j) {
      this->L_[i].setActivationFcts(pf_a, pf_da, j, name);
    }
  }
}

template <int n_in, int n_out, int n_layer>
void mpc<n_in, n_out, n_layer>::setFct(double (*pf_a)(double),
                                       double (*pf_da)(double), int i_layer,
                                       std::string name) {
  for (std::size_t j = 0; j < this->L_[i_layer].getNbNeurons(); ++j) {
    this->L_[i_layer].setActivationFcts(pf_a, pf_da, j, name);
  }
}

template <int n_in, int n_out, int n_layer>
void mpc<n_in, n_out, n_layer>::build(int *Nb_Neurons, int size) {
  if (size != n_layer) {
    std::cout << "Error build: the number of layer and the size of the array "
                 "must be the same.\n             size req: "
              << n_layer << " , given : " << size << std::endl;
    exit(1);
  }
  if (size == n_layer) {
    // Neurons of first layer have a size of n_in.
    this->L_[0] = layer(n_in, Nb_Neurons[0]);
    // The neurons of the other layers have a size of the output of the previous
    // layer, ie the nb of neurons on the previous layer.
    for (int i = 1; i < n_layer; ++i) {
      this->L_[i] = layer(this->L_[i - 1].getNbNeurons(), Nb_Neurons[i]);
    }
    // Construction of the last layer, ie the external layer.
    this->L_[n_layer] = layer(this->L_[n_layer - 1].getNbNeurons(), n_out);

    this->nb_total_weights_ = this->getTotalWeights();
  }
}

// ! Tests

template <int n_in, int n_out, int n_layer>
void mpc<n_in, n_out, n_layer>::unitTest() {

  mpc<n_in, n_out, n_layer> m;

  // Test default constructor
  assert(m.nb_total_weights_ == m.getTotalWeights());
  assert(m.L_[0].getNbData() == n_in);
  assert(m.L_[n_layer].getNbNeurons() == n_out);

  for (int i = 1; i < n_layer + 1; ++i) {
    assert(m.L_[i].getNbData() == m.L_[i - 1].getNbNeurons());
  }

  // Test copy construtor
  mpc<n_in, n_out, n_layer> m2(m);

  assert(m.nb_total_weights_ == m2.getTotalWeights());
  assert(m.nb_total_weights_ == m2.nb_total_weights_);

  for (int i = 0; i < n_layer + 1; ++i) {
    assert(m.L_[i].getNbData() == m2.L_[i].getNbData());
    assert(m.L_[i].getNbNeurons() == m2.L_[i].getNbNeurons());

    for (std::size_t j = 0; j < m.L_[i].getNbNeurons(); ++j) {
      assert(m.L_[i](j).getSizeX() == m2.L_[i](j).getSizeX());
    }
  }

  // Test set activation fcts
  double (*pf_a)(double) = &sigma;
  double (*pf_da)(double) = &dSigma;

  m.setAllFct(pf_a, pf_da, "sigmoid");
  for (int i = 0; i < n_layer + 1; ++i) {
    for (std::size_t j = 0; j < m.L_[i].getNbNeurons(); j++) {
      assert(m(i)(j).evaluateFct(2.2) == pf_a(2.2));
      assert(m(i)(j).evaluateFctDerivative(2.2) == pf_da(2.2));
    }
  }

  double (*pf_h)(double) = &inv;

  m.setFct(pf_h, pf_h, 0);
  for (std::size_t j = 0; j < m.L_[0].getNbNeurons(); j++) {
    assert(m(0)(j).evaluateFct(2.2) == -2.2);
    assert(m(0)(j).evaluateFctDerivative(-3) == 3);
  }

  // The build method is tested in test_mpc.cpp with real values.
}

#endif