#include "../include/neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

// the member list initializer of all constructors in the project are
// initialized in the order declarred in the class as suggested by -Weffc++
// in case some variable depend on each other
neuron::neuron()
    : size_X_{1}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{&ReLU}, pf_activation_d_{&dReLU},
      activation_fct_name_{"ReLU"}, Weight_{new double[2]{
                                        1, 0}}, // biais at the end of the array
      Weight_d_{new double[2]{0, 0}}            // db at the end of the array
{}

neuron::neuron(int n)
    : size_X_{n}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{&ReLU}, pf_activation_d_{&dReLU},
      activation_fct_name_{"ReLU"}, Weight_{new double[n + 1]},
      Weight_d_{new double[n + 1]} {

  if (n <= 0) {
    std::cout
        << "Error: a neuron must take an entry vector of at least size 1.\n";
    exit(1);
  }

  for (int i = 0; i < n; ++i) {
    Weight_[i] = 1;   // the weights are set to 1 by default
    Weight_d_[i] = 0; // the weights derivatives are set to 0 by default
  }

  Weight_[n] = 0;   // the biais is stored at the end of the array
  Weight_d_[n] = 0; // same for db the derivative of biais
}

neuron::neuron(int n, double (*pf_a)(double), double (*pf_da)(double),
               std::string fct_name)
    : size_X_{n}, pre_activation_value_{0}, post_activation_value_{0},
      pf_activation_{pf_a}, pf_activation_d_{pf_da},
      activation_fct_name_{fct_name}, Weight_{new double[n + 1]},
      Weight_d_{new double[n + 1]} {

  if (n <= 0) {
    std::cout
        << "Error: a neuron must take an entry vector of at least size 1.\n";
    exit(1);
  }

  for (int i = 0; i < n; ++i) {
    Weight_[i] = 1;
    Weight_d_[i] = 0;
  }

  Weight_[n] = 0;   // biais
  Weight_d_[n] = 0; // db
}

neuron::neuron(const neuron &ne)
    : size_X_{ne.size_X_}, pre_activation_value_{ne.pre_activation_value_},
      post_activation_value_{ne.post_activation_value_},
      pf_activation_{ne.pf_activation_}, pf_activation_d_{ne.pf_activation_d_},
      activation_fct_name_{ne.activation_fct_name_},
      Weight_{new double[ne.size_X_ + 1]}, Weight_d_{
                                               new double[ne.size_X_ + 1]} {

  // we need to copy to size_X + 1 to copy the biais and db as well
  for (int i = 0; i < (size_X_ + 1); ++i) {
    Weight_[i] = ne.Weight_[i];
    Weight_d_[i] = ne.Weight_d_[i];
  }
}

// Weight_ and Weight_d_ are at least initialized will nullptr -> no errors
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

    delete[] Weight_;   // we need to delete those to create new ones
    delete[] Weight_d_; // with the new size

    Weight_ = new double[size_X_ + 1];   // +1 to stored the biais at the end
    Weight_d_ = new double[size_X_ + 1]; // idem for db

    for (int i = 0; i < size_X_ + 1; ++i) {
      Weight_[i] = ne.Weight_[i];
      Weight_d_[i] = ne.Weight_d_[i];
    }
  }
  return *this;
}

int neuron::getSizeX() const { return size_X_; }

double neuron::getBiais() const { return Weight_[size_X_]; }

double neuron::getDb() const { return Weight_d_[size_X_]; }

double neuron::getWeight(int i) const {
  double weight = 0;

  if (i < size_X_ && i >= 0)
    weight = Weight_[i];

  return weight;
}

double neuron::getWeightDerivative(int i) const {
  if (i < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }
  double dw = 0;

  if (i < size_X_ && i >= 0)
    dw = Weight_d_[i];

  return dw;
}

double neuron::getPe() const { return pre_activation_value_; }

double neuron::getPo() const { return post_activation_value_; }

void neuron::setBiais(double b) { Weight_[size_X_] = b; }

void neuron::setDb(double db) { Weight_d_[size_X_] = db; }

void neuron::setWeight(double w, int i) {
  if (i < size_X_ && i >= 0)
    Weight_[i] = w;
}

void neuron::setWeightDerivative(double dw, int i) {
  if (i < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }
  if (i < size_X_ && i >= 0)
    Weight_d_[i] = dw;
}

void neuron::setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                               std::string name) {
  pf_activation_ = pf_a;
  pf_activation_d_ = pf_da;
  activation_fct_name_ = name;
}

void neuron::setWeightsOnes() {
  for (int i = 0; i < size_X_; ++i) {
    Weight_[i] = 1;
  }
}

void neuron::setWeightsDerivativesZeros() {
  for (int i = 0; i < size_X_; ++i) {
    Weight_d_[i] = 0;
  }
}

void neuron::setWeightsRandom(int a, int b) {
  std::random_device rd;
  std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> dis(a, b);

  for (int i = 0; i < size_X_; ++i)
    Weight_[i] = dis(gen);
}

void neuron::activateNeuron(const double *X, int size) {
  if (size == size_X_) {
    double dot = 0;

    for (int i = 0; i < size_X_; ++i) {
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

  for (int i = 0; i < size_X_ + 1; ++i) {
    if (Weight_[i] != ne.Weight_[i] || Weight_d_[i] != ne.Weight_d_[i])
      return false;
  }

  return true;
}

bool neuron::operator!=(const neuron &ne) const { return !(*this == ne); }

void neuron::printWeights(const double *arr) const {
  if (arr != nullptr) {
    std::cout << "[";
    for (int i = 0; i < size_X_ - 1; ++i) {
      std::cout << arr[i] << ", ";
    }
    std::cout << arr[size_X_ - 1] << "] \n";
  } else {
    std::cout << "the array is empty \n";
  }
}

void neuron::setActivationFctName(std::string name) {
  activation_fct_name_ = name;
}

std::ostream &operator<<(std::ostream &os, const neuron &ne) {
  os << "This neuron is define with : \n"
     << "    An entry vector X of size : " << ne.getSizeX() << "\n"
     << "    A vector of weights : ";
  ne.printWeights(ne.Weight_);
  os << "    A vector of weight's derivatives : ";
  ne.printWeights(ne.Weight_d_);
  os << "    A biais b : " << ne.getBiais()
     << ", its derivative db : " << ne.getDb() << "\n"
     << "    An activation function named : " << ne.activation_fct_name_ << "\n"
     << "    A pre activation value of : " << ne.pre_activation_value_ << "\n"
     << "    A post activation value of : " << ne.post_activation_value_
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
