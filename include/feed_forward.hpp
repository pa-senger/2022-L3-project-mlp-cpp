#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "layer.hpp"

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
  FeedForward();
  FeedForward(const FeedForward &fw);
  FeedForward(double (*pf_loss)(double));
  FeedForward &operator=(const FeedForward &fw) = default;
  ~FeedForward();
  // todo : test constructors, def construc(pf_loss)

private:
  double *X_;
  layer *L_;
  int nb_total_weights_;
};

// * Definitions

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward()
    : X_(new double[n_in]), L_(new layer[n_layer + 1]), nb_total_weights_(0) {

  // for each layer we look at the number of neurons in the layer,
  // for each neurons we look at its size, neuron size = dim X = dim W
  // we use the layer overloaded () operator which return the ref of a neuron
  for (int i = 0; i < n_layer + 1; ++i) {
    for (int j = 0; j < L_[i].getNbNeurons(); ++j) {
      nb_total_weights_ += L_[i](j).getSizeX();
    }
  }
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward(const FeedForward &fw)
    : X_(new double[n_in]), L_(new layer[n_layer + 1]),
      nb_total_weights_(fw.nb_total_weights_) {

  for (int i = 0; i < n_layer + 1; ++i)
    L_[i] = fw.L_[i]; // layer operator = is properly overloaded
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

#endif