#ifndef NEURON_HPP
#define NEURON_HPP

#include "../include/activation_functions.hpp"

#include <cstddef>
#include <iostream>
#include <string>

class neuron {
public:
  // * Construtors && Destructor && Affectation
  // This default constructor defines a neuron with :
  // size_X_ = 1
  // pre_activation_value = post_activation_value = 0
  // the activation fcts ReLU and its derivative
  // Weights_ an array of size 2 with weight=1 and the biais=0 at the end
  // Weights_d_ an array of size 2 with dw=0 and db=0 stored at the end
  neuron();
  // This constructor takes the size n of the entry vector of a neuron.
  // The weigths are sets to 1, their derivatives to 0.
  // The biais and its derivative db are set to 0.
  // The activation fct is set as ReLU.
  neuron(const std::size_t n);
  // This constructor takes the activation fct and its derivative as parameters.
  neuron(const std::size_t n, double (*pf_a)(double), double (*pf_da)(double),
         std::string fct_name = "n/a");
  // This is a copy constructor, arrays are deep copied not shared.
  neuron(const neuron &ne);
  neuron &operator=(const neuron &ne);
  ~neuron();

  // * Getters && Setters

  std::size_t getSizeX() const { return size_X_; }
  double getBiais() const { return Weight_[size_X_]; }
  double getDb() const { return Weight_d_[size_X_]; }
  double getWeight(const std::size_t i) const { return Weight_[i]; }
  double getWeightDerivative(const std::size_t i) const { return Weight_d_[i]; }
  // pre activation value
  inline double getPe() const { return pre_activation_value_; }
  // post activation value
  inline double getPo() const { return post_activation_value_; }
  inline void setBiais(double b) { Weight_[size_X_] = b; }
  inline void setDb(double db) { Weight_d_[size_X_] = db; }
  inline void setWeight(double w, const std::size_t i) { Weight_[i] = w; }
  inline void setWeightDerivative(double dw, const std::size_t i) {
    Weight_d_[i] = dw;
  }
  void setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                         std::string name = "n/a");
  void setActivationFctName(std::string name);

  // * Operators
  // 2 neurons are said to be equal if they have :
  // the same weights and weights derivatives,
  // the same biais and biais derivatives,
  // the same activation function.
  bool operator==(const neuron &ne) const;
  bool operator!=(const neuron &ne) const;
  friend std::ostream &operator<<(std::ostream &os, const neuron &ne);

  // * Other methods
  void setWeightsOnes();
  // The distribution used for the random weights is Unif([a, b])
  void setWeightsRandom(int a, int b);
  void setWeightsDerivativesZeros();
  // The activation of neuron is the composition :
  // activation_fct( pre_activation_value ),
  // with pre_activation_value = (<X,W> + biais),
  // where X is the entry vector, W the vector of weights Weights_ and
  // <.,.> is the euclidian dot product.
  // The result is a double stored in post_activation_value.
  void activateNeuron(const double *X, const std::size_t size);
  void printArr(const double *arr) const;
  double evaluateFct(double x) const;           // activation_fct(x)
  double evaluateFctDerivative(double x) const; // activation_fct_derivative(x)

  // * Tests
  static void unitTest();

private:
  std::size_t size_X_; // The size of the entry vector of the neuron.
  double pre_activation_value_;
  double post_activation_value_;
  double (*pf_activation_)(double);
  double (*pf_activation_d_)(double);
  std::string activation_fct_name_;
  double *Weight_;   // The biais will be stored at the end of the array.
  double *Weight_d_; // db will be stored at the end of the array.
};

#endif