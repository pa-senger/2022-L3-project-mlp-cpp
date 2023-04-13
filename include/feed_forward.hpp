#ifndef FEED_FORWARD_HPP
#define FEED_FORWARD_HPP
#include "activation_functions.hpp"
#include "layer.hpp"
#include <cassert>
#include <cstddef>
#include <ostream>

template <int n_in, int n_out, int n_layer> class FeedForward {
public:
  // * Constructors && Destructor && Affectation
  FeedForward();
  FeedForward(const FeedForward &fw);
  // FeedForward(double (*pf_loss)(double));
  FeedForward &operator=(const FeedForward &fw);
  virtual ~FeedForward();

  // * Getters && Setters
  std::size_t getTotalWeights() const;
  void setAllWeightsRandoms(const double a, const double b);
  void setAllWeightsDerivativesZeros();
  void setAllWeights(double *arr, std::size_t size);
  void getAllWeights(double *arr, std::size_t size) const;
  double *getY() const { return Y_; }
  void printY() const;

  // * Operators
  layer &operator()(std::size_t i_layer) const;

  template <int I, int O, int L>
  friend std::ostream &operator<<(std::ostream &os,
                                  const FeedForward<I, O, L> &ff);

  // * Other methods
  double *evaluate(const double *X, const std::size_t size);
  virtual void build(__attribute__((unused)) int *Nb_Neurons,
                     __attribute__((unused)) int size) {}

  // * Tests
  static void unitTest();

protected:
  double *X_; // Array of entry data.
  layer *L_;  // Array of layers of size n_layer+1 (n_layer hidden layer).
  std::size_t nb_total_weights_;
  double *Y_; // Array, output of the network after evaluation.
};

// ! Definitions

// This default constructor sets n_layer+1 layers,
// Each layer contains n_out neurons.
template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward()
    : X_(nullptr), L_(new layer[n_layer + 1]), nb_total_weights_(0),
      Y_(nullptr) {

  if (n_in > 0 && n_out > 0) {
    X_ = new double[n_in];
    Y_ = new double[n_out];
  }
  // Neurons of first layer have a size of n_in.
  L_[0] = layer(n_in, n_out);
  // The neurons of the other layers have a size of the output of the previous
  // layer, ie the nb of neurons of the previous layer.
  for (int i = 1; i < n_layer + 1; ++i) {
    L_[i] = layer(L_[i - 1].getNbNeurons(), n_out);
  }

  nb_total_weights_ = getTotalWeights();
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::FeedForward(const FeedForward &fw)
    : X_(nullptr), L_(new layer[n_layer + 1]),
      nb_total_weights_(fw.nb_total_weights_), Y_(nullptr) {

  if (n_in > 0 && n_out > 0) {
    X_ = new double[n_in];
    Y_ = new double[n_out];

    for (int i = 0; i < n_in; ++i)
      X_[i] = fw.X_[i];

    for (int i = 0; i < n_out; ++i)
      Y_[i] = fw.Y_[i];

    for (int i = 0; i < n_layer + 1; ++i)
      L_[i] = fw.L_[i]; // Layer operator = is properly overloaded.
  }
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer> &
FeedForward<n_in, n_out, n_layer>::operator=(const FeedForward &fw) {
  if (this != &fw) {
    nb_total_weights_ = fw.nb_total_weights_;

    delete[] X_;
    delete[] L_;
    delete[] Y_;
    X_ = nullptr;
    Y_ = nullptr;

    L_ = new layer[n_layer + 1];
    for (int i = 0; i < (n_layer + 1); ++i)
      L_[i] = fw.L_[i];

    if (fw.X_ != nullptr) {
      X_ = new double[n_in];
      Y_ = new double[n_out];
      for (int i = 0; i < n_in; ++i)
        X_[i] = fw.X_[i];
      for (int i = 0; i < n_out; ++i)
        Y_[i] = fw.Y_[i];
    }
  }

  return *this;
}

template <int n_in, int n_out, int n_layer>
FeedForward<n_in, n_out, n_layer>::~FeedForward() {
  delete[] X_;
  delete[] L_; // The destructor from layer will be called.
  delete[] Y_;
}

// This is the number of weights in the network not the sum of the weights.
template <int n_in, int n_out, int n_layer>
std::size_t FeedForward<n_in, n_out, n_layer>::getTotalWeights() const {
  std::size_t res = 0;
  for (int i = 0; i < n_layer + 1; ++i) {
    for (std::size_t j = 0; j < L_[i].getNbNeurons(); ++j) {
      // For each layer we look at the number of neurons in the layer,
      // for each neurons we look at its size, neuron size = dim X = dim W,
      // we use the layer overloaded () operator which return a &neuron by ref.
      res += L_[i](j).getSizeX();
    }
  }
  return res;
}

// This methods uses the Unif([a,b]) distribution to set random weights.
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeightsRandoms(const double a,
                                                             const double b) {
  for (int i = 0; i < n_layer + 1; ++i)
    L_[i].setAllWeightsRandoms(a, b);
}

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeightsDerivativesZeros() {
  for (int i = 0; i < n_layer + 1; ++i)
    L_[i].setAllWeightsDerivativesZeros();
}

template <int n_in, int n_out, int n_layer>
layer &
FeedForward<n_in, n_out, n_layer>::operator()(std::size_t i_layer) const {
  if (i_layer > n_layer + 1) {
    std::cout
        << "Error operator(): there isn't as many layers in the system! \n";
    exit(1);
  }

  return L_[i_layer];
}

// This method sets the weights for the whole network.
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::setAllWeights(double *arr,
                                                      std::size_t size) {
  if (size == getTotalWeights()) {
    int index = 0; // to keep track of where we are in arr.
    for (int i = 0; i < n_layer + 1; ++i) {
      for (std::size_t j = 0; j < L_[i].getNbNeurons(); ++j)
        for (std::size_t k = 0; k < L_[i](j).getSizeX(); ++k) {
          L_[i].setWeight(arr[index++], j, k);
          // std::cout << L_[i](j).getWeight(k) << std::endl;
        }
    }
  } else {
    std::cout << "Error setAllWeights: the array containing the weights "
                 "should be of size : "
              << getTotalWeights() << std::endl;
  }
}

// To avoid the "ISO C++ forbids variable length array" error we pass an array
// to the method as parameter and the method fills it instead of
// making a new array in the method and returning it
// this problem could be avoided using std::vectors (i think?)
template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::getAllWeights(double *arr,
                                                      std::size_t size) const {
  if (size == getTotalWeights()) {
    int index = 0; // to keep track of where we are in arr.
    for (int i = 0; i < n_layer + 1; ++i) {
      for (std::size_t j = 0; j < L_[i].getNbNeurons(); j++)
        for (std::size_t k = 0; k < L_[i](j).getSizeX(); ++k) {
          arr[index++] = L_[i].getWeight(j, k);
          // std::cout << L_[i].getWeight(j, k) << std::endl;
        }
    }
  }
}

template <int n_in, int n_out, int n_layer>
double *FeedForward<n_in, n_out, n_layer>::evaluate(const double *X,
                                                    const std::size_t size) {
  if (size != n_in || n_in <= 0 || n_out <= 0) {
    std::cout << "Error evaluate: size required : " << n_in
              << " ,size given : " << size << std::endl;
    exit(1);
  }
  for (int i = 0; i < n_in; ++i)
    X_[i] = X[i];

  double *Y0 = L_[0].evaluateLayer(X, size);
  for (int i = 1; i < n_layer; ++i) {
    double *Y = L_[i].evaluateLayer(Y0, L_[i - 1].getNbNeurons());
    Y0 = Y;
  }
  Y_ = L_[n_layer].evaluateLayer(Y0, L_[n_layer - 1].getNbNeurons());
  return getY();
}

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::printY() const {
  if (Y_ != nullptr) {
    std::cout << "Y = [";
    for (int i = 0; i < n_out - 1; ++i) {
      std::cout << Y_[i] << ", ";
    }
    std::cout << Y_[n_out - 1] << "] \n";
  } else {
    std::cout << "Y = [] \n";
  }
}
template <int n_in, int n_out, int n_layer>
std::ostream &operator<<(std::ostream &os,
                         const FeedForward<n_in, n_out, n_layer> &ff) {
  os << "This neural network is define with: "
     << "\n    A number of weights: " << ff.nb_total_weights_ << "\n    ";
  ff.printY();

  return os;
};

// ! Tests

template <int n_in, int n_out, int n_layer>
void FeedForward<n_in, n_out, n_layer>::unitTest() {

  // Test default constructor
  FeedForward<n_in, n_out, n_layer> fw1;

  // getTotalWeights is also tested with real values in test_feed-forward.cpp
  // assert(fw1.nb_total_weights_ == fw1.getTotalWeights());
  // assert(fw1.L_[0].getNbData() == n_in);
  // assert(fw1.L_[n_layer].getNbNeurons() == n_out);

  for (int i = 1; i < n_layer + 1; ++i) {
    assert(fw1.L_[i].getNbData() == fw1.L_[i - 1].getNbNeurons());
  }

  // Test copy construtor
  FeedForward<n_in, n_out, n_layer> fw2(fw1);

  assert(fw1.nb_total_weights_ == fw2.getTotalWeights());
  assert(fw1.nb_total_weights_ == fw2.nb_total_weights_);

  for (int i = 0; i < n_layer + 1; ++i) {
    assert(fw1.L_[i].getNbData() == fw2.L_[i].getNbData());
    assert(fw1.L_[i].getNbNeurons() == fw2.L_[i].getNbNeurons());

    for (std::size_t j = 0; j < fw1.L_[i].getNbNeurons(); ++j) {
      assert(fw1.L_[i](j).getSizeX() == fw2.L_[i](j).getSizeX());
    }
  }

  fw1.setAllWeightsDerivativesZeros();
  for (int i = 0; i < n_layer + 1; ++i) {
    for (std::size_t j = 0; j < fw1.L_[i].getNbNeurons(); ++j) {
      for (std::size_t k = 0; k < fw1(i)(j).getSizeX(); ++k)
        assert(fw1(i)(j).getWeightDerivative(k) == 0);
    }
  }

  fw1.setAllWeightsRandoms(0, 1);
  for (int i = 0; i < n_layer + 1; ++i) {
    for (std::size_t j = 0; j < fw1.L_[i].getNbNeurons(); ++j) {
      for (std::size_t k = 0; k < fw1(i)(j).getSizeX() - 1; ++k) {
        // Unless we're very unlucky all weights should be differents.
        assert(fw1(i)(j).getWeight(k) != fw1(i)(j).getWeight(k + 1));
        // std::cout << fw1(i)(j).getWeight(k) << std::endl;
      }
    }
  }

  // Test () operator
  for (int i = 0; i < n_layer + 1; ++i)
    assert(fw1(i) == fw1.L_[i]);

  // Test setAllWeights(arr, size arr) && getAllWeights(arr, size arr)
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

  // The evaluate method is tested with real values in test_feed-forward.cpp
}

#endif
