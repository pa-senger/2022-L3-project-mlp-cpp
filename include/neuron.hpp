#ifndef NEURON_HPP
#define NEURON_HPP

#include "../include/activation_functions.hpp"

#include <iostream>
#include <string>

class neuron {
public:
  // this default constructor defines a neuron with :
  // sizeX_ = 1
  // pre_activation_value = post_activation_value = 0
  // the activation fcts ReLU and its derivative
  // Weights_ an arrays of size 2 with weight=1 and the biais=0 stored at the
  // end Weights_d_ an arrays of size 2 with dw=0 and  db=0 stored at the end
  neuron();
  // this constructor takes the size n of the entry vector of a neuron
  neuron(int n);
  // this constructor takes the activation fct and its derivative
  neuron(int n, double (*pf_a)(double), double (*pf_da)(double),
         std::string fct_name = "n/a");
  // this is a copy constructor, arrays are deep copied not shared
  neuron(const neuron &ne);
  // destructor
  ~neuron();

  // getter setter
  int getSizeX() const;
  double getBiais() const;
  double getDb() const;
  double getWeight(int i) const;
  double getWeightDerivative(int i) const;
  double getPe() const;
  double getPo() const;

  void setBiais(double b);
  void setDb(double db);
  void setWeight(double Weight, int i);
  void setWeightDerivative(double dWeight, int i);
  void setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                         std::string name = "n/a");
  void setActivationFctName(std::string name);

  // operator
  neuron operator=(const neuron &ne);
  bool operator==(const neuron &ne) const;
  bool operator!=(const neuron &ne) const;
  friend std::ostream &operator<<(std::ostream &os, const neuron &ne);

  // methods
  void setWeightsOnes();
  // the distribution used for the random weights is Unif([-1m, 1m])
  void setWeightsRandom();
  void setWeightsDerivativesZeros();
  // the activation of neuron is the compositon :
  // activation_fct( pre_activation_value )
  // with pre_activation_value = ((X.W) + biais)
  // where X is the entry vector, W the vector of weights Weights_
  // the result is a double stored in post_activation_value
  void activateNeuron(const double *X, int size);
  void printWeights(const double *arr) const;
  double evaluateFct(double x) const;           // activation_fct(x)
  double evaluateFctDerivative(double x) const; // activation_fct_derivative(x)

  // tests
  static int unitTest1(); // tests constuctors
  static int unitTest2(); // tests getters setters
  static int unitTest3(); // tests operators and methods

private:
  int size_X_; // the size of the entry vector of the neuron
  double pre_activation_value_;
  double post_activation_value_;
  double (*pf_activation_)(double);
  double (*pf_activation_d_)(double);
  std::string activation_fct_name_;
  double *Weight_;   // the biais will be stored at the end of the array
  double *Weight_d_; // db will be stored at the end of the array
};

#endif