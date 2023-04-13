#include "../include/neuron.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <random>

// The member list initializer of all constructors in the project are
// initialized in the order declarred in the class as suggested by -Weffc++
// in case some variable depend on each other.
neuron::neuron()
    : size_X_{1}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{&ReLU}, pf_activation_d_{&dReLU},
      activation_fct_name_{"ReLU"}, Weight_{new double[2]{
                                        1,
                                        0}}, // Biais at the end of the array.
      Weight_d_{new double[2]{0, 0}}         // db at the end of the array.
{}

neuron::neuron(const std::size_t n)
    : size_X_{n}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{&ReLU}, pf_activation_d_{&dReLU},
      activation_fct_name_{"ReLU"}, Weight_{new double[n + 1]},
      Weight_d_{new double[n + 1]} {

  if (n <= 0) {
    std::cout << "Error constructor: a neuron must take an entry vector of at "
                 "least size 1.\n";
    exit(1);
  }

  for (std::size_t i = 0; i < n; ++i) {
    Weight_[i] = 1;   // The weights are set to 1 by default.
    Weight_d_[i] = 0; // The weights derivatives are set to 0 by default.
  }

  Weight_[n] = 0;   // The biais is stored at the end of the array.
  Weight_d_[n] = 0; // Same for db the derivative of biais.
}

neuron::neuron(const std::size_t n, double (*pf_a)(double),
               double (*pf_da)(double), std::string fct_name)
    : size_X_{n}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{pf_a}, pf_activation_d_{pf_da},
      activation_fct_name_{fct_name}, Weight_{new double[n + 1]},
      Weight_d_{new double[n + 1]} {

  if (n <= 0) {
    std::cout << "Error construtor: a neuron must take an entry vector of at "
                 "least size 1.\n";
    exit(1);
  }

  for (std::size_t i = 0; i < n; ++i) {
    Weight_[i] = 1;
    Weight_d_[i] = 0;
  }

  Weight_[n] = 0;   // Biais.
  Weight_d_[n] = 0; // Biais derivative db.
}

neuron::neuron(const neuron &ne)
    : size_X_{ne.size_X_}, pre_activation_value_{ne.pre_activation_value_},
      post_activation_value_{ne.post_activation_value_},
      pf_activation_{ne.pf_activation_}, pf_activation_d_{ne.pf_activation_d_},
      activation_fct_name_{ne.activation_fct_name_},
      Weight_{new double[ne.size_X_ + 1]}, Weight_d_{
                                               new double[ne.size_X_ + 1]} {

  // We need to copy to size_X + 1 to copy the biais and db as well.
  for (std::size_t i = 0; i < (size_X_ + 1); ++i) {
    Weight_[i] = ne.Weight_[i];
    Weight_d_[i] = ne.Weight_d_[i];
  }
}

// Weight_ and Weight_d_ are at least initialized will nullptr -> no errors.
neuron::~neuron() {
  delete[] Weight_;
  delete[] Weight_d_;
}

neuron &neuron::operator=(const neuron &ne) {
  if (this != &ne) {
    size_X_ = ne.size_X_;
    pre_activation_value_ = ne.pre_activation_value_;
    post_activation_value_ = ne.post_activation_value_;
    pf_activation_ = ne.pf_activation_;
    pf_activation_d_ = ne.pf_activation_d_;

    delete[] Weight_;   // We need to delete those to create new ones with
    delete[] Weight_d_; // the right size.

    Weight_ = new double[size_X_ + 1];   // +1 to stored the biais at the endi
    Weight_d_ = new double[size_X_ + 1]; // Idem for db.

    for (std::size_t i = 0; i < size_X_ + 1; ++i) {
      Weight_[i] = ne.Weight_[i];
      Weight_d_[i] = ne.Weight_d_[i];
    }
  }
  return *this;
}

void neuron::setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                               std::string name) {
  pf_activation_ = pf_a;
  pf_activation_d_ = pf_da;
  activation_fct_name_ = name;
}

void neuron::setWeightsOnes() {
  for (std::size_t i = 0; i < size_X_; ++i) {
    Weight_[i] = 1;
  }
}

void neuron::setWeightsDerivativesZeros() {
  for (std::size_t i = 0; i < size_X_; ++i) {
    Weight_d_[i] = 0;
  }
}

void neuron::setWeightsRandom(int a, int b) {
  std::random_device rd;
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> dis(a, b);

  for (std::size_t i = 0; i < size_X_; ++i)
    Weight_[i] = dis(gen);
}

void neuron::activateNeuron(const double *X, const std::size_t size) {
  if (size == size_X_) {
    double dot = 0;

    for (std::size_t i = 0; i < size_X_; ++i) {
      dot += (Weight_[i] * X[i]);
    }
    pre_activation_value_ = dot + getBiais();
    post_activation_value_ = pf_activation_(pre_activation_value_);
  }
}

bool neuron::operator==(const neuron &ne) const {
  if (size_X_ != ne.size_X_ || pf_activation_ != ne.pf_activation_ ||
      pf_activation_d_ != ne.pf_activation_d_)
    return false;

  for (std::size_t i = 0; i < size_X_ + 1; ++i) {
    if (Weight_[i] != ne.Weight_[i] || Weight_d_[i] != ne.Weight_d_[i])
      return false;
  }

  return true;
}

bool neuron::operator!=(const neuron &ne) const { return !(*this == ne); }

void neuron::printArr(const double *arr) const {
  if (arr != nullptr) {
    std::cout << "[";
    for (std::size_t i = 0; i < size_X_ - 1; ++i) {
      std::cout << arr[i] << ", ";
    }
    std::cout << arr[size_X_ - 1] << "] \n";
  } else {
    std::cout << "[] \n";
  }
}

void neuron::setActivationFctName(std::string name) {
  activation_fct_name_ = name;
}

std::ostream &operator<<(std::ostream &os, const neuron &ne) {
  os << "This neuron is define with : \n"
     << "    An entry vector X of size : " << ne.getSizeX()
     << "\n    A vector of weights : ";
  ne.printArr(ne.Weight_);
  os << "    A vector of weight's derivatives : ";
  ne.printArr(ne.Weight_d_);
  os << "    A biais b : " << ne.getBiais()
     << ", its derivative db : " << ne.getDb()
     << "\n    An activation function named : " << ne.activation_fct_name_
     << "\n    A pre activation value of : " << ne.pre_activation_value_
     << "\n    A post activation value of : " << ne.post_activation_value_
     << "\n";

  return os;
}

double neuron::evaluateFct(double x) const {
  double res = 0;

  if (pf_activation_ != nullptr)
    res = pf_activation_(x);

  return res;
}

double neuron::evaluateFctDerivative(double x) const {
  double res = 0;

  if (pf_activation_d_ != nullptr)
    res = pf_activation_d_(x);

  return res;
}
