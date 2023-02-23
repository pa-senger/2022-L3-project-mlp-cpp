#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "layer.hpp"

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
private:
  double *X_;
  layer *L_;
  int nb_total_weights_;
};

#endif