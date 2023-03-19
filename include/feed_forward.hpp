#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "layer.hpp"
#include <cassert>

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
  FeedForward();
  FeedForward(const FeedForward &fw);
  // FeedForward(double (*pf_loss)(double));
  FeedForward &operator=(const FeedForward &fw);
  ~FeedForward();

  int getTotalWeights() const;
  void setAllWeightsRandoms(double a, double b);
  void setAllWeightsDerivativesZeros();
  void setAllWeights(double *arr, int size);
  void getAllWeights(double *arr, int size) const;

  layer &operator()(int i_layer) const;
  double *evaluate(double *X, int size);

  void unitTest();

private:
  double *X_; // array of entry data
  layer *L_;  // array of layers of size n_layer+1
  int nb_total_weights_;
  double *Y_;
};

// * Definitions

// this default constructor sets n_layer+1 layers
// each layer contains n_out neurons of size n_in
template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward()
    : X_(new double[n_in]), L_(new layer[n_layer + 1]), nb_total_weights_(0),
      Y_(new double[n_out]) {

  L_[0] = layer(n_in, n_out);
  for (int i = 1; i < n_layer; ++i) {
    L_[i] = layer(L_[i - 1].getNbNeurons(), n_out);
  }

  L_[n_layer] = layer(L_[n_layer - 1].getNbNeurons(), n_out);

  nb_total_weights_ = getTotalWeights();
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward(const FeedForward &fw)
    : X_(new double[n_in]), L_(new layer[n_layer + 1]),
      nb_total_weights_(fw.nb_total_weights_), Y_(new double[n_out]) {

  for (int i = 0; i < n_in; ++i)
    X_[i] = fw.X_[i];

  for (int i = 0; i < n_out; ++i)
    Y_[i] = fw.Y_[i];

  for (int i = 0; i < n_layer + 1; ++i)
    L_[i] = fw.L_[i]; // layer operator = is properly overloaded
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer> &
FeedForward<n_in, n_out, n_layer>::operator=(const FeedForward &fw) {
  if (this != &fw) {
    delete[] X_;
    delete[] L_;
    delete[] Y_;
    nb_total_weights_ = fw.nb_total_weights_;

    X_ = new double[n_in];
    Y_ = new double[n_out];
    L_ = new layer[n_layer + 1];

    for (int i = 0; i < n_in; ++i)
      X_[i] = fw.X_[i];
    for (int i = 0; i < n_out; ++i)
      Y_[i] = fw.Y_[i];
    for (int i = 0; i < (n_layer + 1); ++i)
      L_[i] = fw.L_[i];
  }

  return *this;
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::~FeedForward() {
  delete[] X_;
  delete[] L_; // the destructor from layer will be called
  delete[] Y_;
}

// this is the number of weights in the network not the sum of the weights
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

// this methods uses the Unif([a,b]) distribution to set random weights
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeightsRandoms(double a,
                                                             double b) {
  for (int i = 0; i < n_layer + 1; ++i)
    L_[i].setAllWeightsRandoms(a, b);
}

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeightsDerivativesZeros() {
  for (int i = 0; i < n_layer + 1; ++i)
    L_[i].setAllWeightsDerivativesZeros();
}

template <int n_in, int n_out, int n_layer>
layer &FeedForward<n_in, n_out, n_layer>::operator()(int i_layer) const {
  if (i_layer > n_layer + 1) {
    std::cout << "Error : there isn't as many layers in the system! \n";
    exit(1);
  }

  return L_[i_layer];
}

// this method sets the weights for the whole network
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeights(double *arr, int size) {
  if (size == getTotalWeights()) {
    int index = 0;
    for (int i = 0; i < n_layer + 1; ++i) {
      for (int j = 0; j < L_[i].getNbNeurons(); ++j)
        for (int k = 0; k < L_[i](j).getSizeX(); ++k) {
          L_[i].setWeight(arr[index++], j, k);
          // std::cout << L_[i](j).getWeight(k) << std::endl;
        }
    }
  } else {
    std::cout << "Error : the array containing the weights should be of size : "
              << getTotalWeights() << std::endl;
  }
}

// to avoid the "ISO C++ forbids variable length array" error we chose to give
// the array to the method as parameter and the method fills it instead of
// making a new array in the method and returning it
// this problem could be avoided using std::vectors
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::getAllWeights(double *arr,
                                                      int size) const {
  if (size == getTotalWeights()) {
    int index = 0;
    for (int i = 0; i < n_layer + 1; ++i) {
      for (int j = 0; j < L_[i].getNbNeurons(); j++)
        for (int k = 0; k < L_[i](j).getSizeX(); ++k) {
          arr[index++] = L_[i].getWeight(j, k);
          // std::cout << L_[i].getWeight(j, k) << std::endl;
        }
    }
  }
}

template <int n_in, int n_out, int n_layer>
double *FeedForward<n_in, n_out, n_layer>::evaluate(double *X, int size) {
  if (size != n_in) {
    std::cout << "Error: size required : " << n_in
              << "\n     size given : " << size << std::endl;
    exit(1);
  }
  double *Y0 = L_[0].evaluateLayer(X, size);
  for (int i = 1; i < n_layer; ++i) {
    double *Y = L_[i].evaluateLayer(Y0, L_[i - 1].getNbNeurons());
    Y0 = Y;
  }
  Y_ = L_[n_layer].evaluateLayer(Y0, L_[n_layer - 1].getNbNeurons());
  return Y_;
}

// * Tests

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::unitTest() {

  // test default constructor
  FeedForward<n_in, n_out, n_layer> fw1;

  assert(fw1.nb_total_weights_ == fw1.getTotalWeights());
  for (int i = 0; i < n_layer + 1; ++i) {
    assert(fw1.L_[i].getNbData() == n_in);
    assert(fw1.L_[0].getNbNeurons() == n_out);

    for (int j = 0; j < fw1.L_[i].getNbNeurons(); ++j) {
      assert(fw1.L_[i](j).getSizeX() == n_in);
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

  fw1.setAllWeightsDerivativesZeros();
  for (int i = 0; i < n_layer + 1; ++i) {
    for (int j = 0; j < fw1.L_[i].getNbNeurons(); ++i) {
      for (int k = 0; k < fw1(i)(j).getSizeX(); ++k)
        assert(fw1(i)(j).getWeightDerivative(k) == 0);
    }
  }

  fw1.setAllWeightsRandoms(0, 1);
  for (int i = 0; i < n_layer + 1; ++i) {
    for (int j = 0; j < fw1.L_[i].getNbNeurons(); ++i) {
      for (int k = 0; k < fw1(i)(j).getSizeX() - 1; ++k) {
        // unless we're very unlucky all weights should be differents
        assert(fw1(i)(j).getWeight(k) != fw1(i)(j).getWeight(k + 1));
        // std::cout << fw1(i)(j).getWeight(k) << std::endl;
      }
    }
  }

  // test () operator
  for (int i = 0; i < n_layer + 1; ++i)
    assert(fw1(i) == L_[i]);

  // test setAllWeights(arr, size arr) && getAllWeights(arr, size arr)
  int size_arr = fw1.getTotalWeights();
  double *W = new double[size_arr];
  for (int i = 0; i < size_arr; ++i)
    W[i] = i;

  fw1.setAllWeights(W, size_arr);
  double *W2 = new double[size_arr];
  fw1.getAllWeights(W2, size_arr);

  for (int i = 0; i < size_arr; ++i)
    assert(W[i] == W2[i]);

  delete[] W;
  delete[] W2;
}

#endif
