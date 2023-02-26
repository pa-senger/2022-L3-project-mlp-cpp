#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "layer.hpp"
#include <cassert>

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
  FeedForward();
  FeedForward(const FeedForward &fw);
  FeedForward(double (*pf_loss)(double));
  FeedForward &operator=(const FeedForward &fw) = default;
  ~FeedForward();
  // todo : test constructors, def construc(pf_loss)

  int getTotalWeights() const;

  void unitTest();

private:
  double *X_; //  array containing the vector for each neuron ?
  layer *L_;  // array of layers
  int nb_total_weights_;
};

// * Definitions

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward()
    : X_(new double[n_out]), L_(new layer[n_layer + 1]),
      nb_total_weights_(n_in * n_out * (n_layer + 1)) {

  // X_ contains a vector of size n_in
  // each neurons in the layer activate with X and return a double y,
  // the layer returns Y[nb_neurons == n_out],
  // Y[nb_neurons] is used by the next layer instead of X
  // and so on
  for (int i = 0; i < n_layer + 1; ++i) {
    // we make the layers identical in size,
    // each activated neuron return a real,
    // if we want a vector[n_out] at the end we need n_out neurons on each layer

    // ! i need to understand the layer system,
    L_[i] = layer(n_in, n_out);
  }
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward(const FeedForward &fw)
    : X_(new double[n_out]), L_(new layer[n_layer + 1]),
      nb_total_weights_(fw.nb_total_weights_) {

  for (int i = 0; i < n_in; ++i) {
    X_[i] = fw.X_[i];
  }

  for (int i = 0; i < n_layer + 1; ++i) {
    L_[i] = fw.L_[i]; // layer operator = is properly overloaded
  }
}

// todo
// template <int n_in, int n_out, int n_layer>
// FeedForward<n_in, n_out, n_layer>::FeedForward(double (*pf_loss)(double)) :
// {}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::~FeedForward() {
  delete[] X_;
  delete[] L_; // the destructor from layer will be called ?
}

template <int n_in, int n_out, int n_layer>
int FeedForward<n_in, n_out, n_layer>::getTotalWeights() const {
  int res = 0;
  for (int i = 0; i < n_layer + 1; ++i) {
    for (int j = 0; j < L_[i].getNbNeurons(); ++j) {
      // for each layer we look at the number of neurons in the layer,
      // for each neurons we look at its size, neuron size = dim X = dim W,
      // we use the layer overloaded () operator which return a &neuron by ref
      res += L_[i](j).getSizeX();
    }
  }
  return res;
}

// * Tests

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::unitTest() {

  // test default constructor
  FeedForward<n_in, n_out, n_layer> fw1;

  assert(fw1.nb_total_weights_ == fw1.getTotalWeights());

  for (int i = 0; i < n_layer + 1; ++i) {
    assert(fw1.L_[i].getNbData() == n_in);
    assert(fw1.L_[i].getNbNeurons() == n_out);

    for (int j = 0; j < L_[i].getNbNeurons(); ++j) {
      assert(L_[i](j).getSizeX() == n_in);
    }
  }

  // test copy construtor
  FeedForward<n_in, n_out, n_layer> fw2(fw1);

  assert(fw1.nb_total_weights_ == fw2.getTotalWeights());
  assert(fw1.nb_total_weights_ == fw2.nb_total_weights_);

  for (int i = 0; i < n_layer + 1; ++i) {
    assert(fw1.L_[i].getNbData() == fw2.L_[i].getNbData());
    assert(fw1.L_[i].getNbNeurons() == fw2.L_[i].getNbNeurons());

    for (int j = 0; j < fw1.L_[i].getNbNeurons(); ++j) {
      assert(fw1.L_[i](j).getSizeX() == fw2.L_[i](j).getSizeX());
    }
  }

  // test contructor taking a loss function
  // todo

  // test get total number of weights in the layer system
  assert(fw1.getTotalWeights() == (n_in * n_out * (n_layer + 1)));
}

#endif