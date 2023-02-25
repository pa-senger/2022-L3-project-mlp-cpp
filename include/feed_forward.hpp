#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "layer.hpp"

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
  FeedForward();

private:
  double *X_;
  layer *L_;
  int nb_total_weights_;
};

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward()
    : X_(new double[n_in]), L_(new layer[n_layer]), nb_total_weights_(0) {

  // for each layer we look at the number of neurons in the layer,
  // for each neurons we look at its size, neuron size = dim X = dim W
  // we use the layer overloaded () operator which return the ref of a neuron
  for (int i = 0; i < n_layer; ++i) {
    for (int j = 0; j < L_[i].getNbNeurons(); ++j) {
      nb_total_weights_ += L_[i](j).getSizeX();
    }
  }
}

#endif