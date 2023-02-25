#include "../include/layer.hpp"
#include "../include/neuron.hpp"

#include <iostream>

// todo : handle errors instead of exiting the program

// this construtor makes a an array of neurons
// each neurons are constructed with :
// -an entry data vector of size nb_data,
// -an array of weights filled with ones
// -a biais of 0
// -an array of weights derivatives filled wirh zeros
// -a derivative of biais set to 0
// -an activation fct and its derivative set as ReLU
// -a pre_activation_value and post_activation_value of 0
// if the arguments are <= 0, the layer of neurons will be empty,
// arrays will still be initialised with nullptr
layer::layer(int nb_data, int nb_neurons)
    : nb_neurons_(nb_neurons), nb_data_(nb_data), arr_neurons_(nullptr),
      Y_(nullptr) {

  if (nb_data < 0 || nb_neurons < 0) {
    std::cout << "Error : a layer can't take a negative number of data nor "
                 "have a negative number of neurons\n";
    exit(1);
  }

  if (nb_neurons != 0) {
    arr_neurons_ = new neuron[nb_neurons];
    Y_ = new double[nb_neurons];

    for (int i = 0; i < nb_neurons; ++i) {
      arr_neurons_[i] = neuron(nb_data);
      Y_[i] = 0;
    }
  }
}

layer::layer(const layer &co)
    : nb_neurons_(co.nb_neurons_), nb_data_(co.nb_data_), arr_neurons_(nullptr),
      Y_(new double[nb_neurons_]) {

  if (co.arr_neurons_ != nullptr && co.nb_neurons_ != 0) {
    arr_neurons_ = new neuron[nb_neurons_];

    for (int i = 0; i < nb_neurons_; ++i) {
      arr_neurons_[i] = co.arr_neurons_[i];
      Y_[i] = co.Y_[i];
    }
  }
}

layer::~layer() {
  delete[] arr_neurons_;
  delete[] Y_;
}

layer &layer::operator=(const layer &l) {
  if (this != &l) {
    nb_neurons_ = l.nb_neurons_;
    nb_data_ = l.nb_data_;
    delete[] arr_neurons_;
    delete[] Y_;

    if (l.arr_neurons_ == nullptr) {
      arr_neurons_ = nullptr;
    } else {
      arr_neurons_ = new neuron[nb_neurons_];
      Y_ = new double[nb_neurons_];

      for (int i = 0; i < nb_neurons_; ++i) {
        arr_neurons_[i] = l.arr_neurons_[i];
        Y_[i] = l.Y_[i];
      }
    }
  }
  return *this;
}

double layer::getWeight(int i_neuron, int j_weight) const {
  double res;

  if (i_neuron < 0 || j_weight < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (nb_neurons_ == 0 || arr_neurons_ == nullptr)
    res = 0;

  if (i_neuron < nb_neurons_ && j_weight < arr_neurons_[i_neuron].getSizeX())
    res = arr_neurons_[i_neuron].getWeight(j_weight);

  return res;
}

double layer::getWeightDerivative(int i_neuron, int j_weight) const {
  double res;

  if (i_neuron < 0 || j_weight < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (nb_neurons_ == 0 || arr_neurons_ == nullptr)
    res = 0;

  if (i_neuron < nb_neurons_ && j_weight < arr_neurons_[i_neuron].getSizeX())
    res = arr_neurons_[i_neuron].getWeightDerivative(j_weight);

  return res;
}

int layer::getNbData() const { return nb_data_; }

double layer::getNbNeurons() const { return nb_neurons_; }

double layer::getPo(int i_neuron) const {
  double res = 0;

  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    res = arr_neurons_[i_neuron].getPo();
  } else {
    std::cout << "Error : there isn't as many neurons in the layer !"
              << std::endl;
  }

  return res;
}

void layer::setWeight(double val, int i_neuron, int j_weight) {
  if (i_neuron < 0 || j_weight < 0) {
    std::cout << "Error : you must use positive integers for this !\n";
    exit(1);
  }

  if (nb_neurons_ == 0 || i_neuron >= nb_neurons_ ||
      j_weight > (arr_neurons_[i_neuron].getSizeX()) ||
      arr_neurons_ == nullptr) {
    std::cout << "Error : there isn't as many neurons or weights ! \n";
    exit(1);
  } else {
    arr_neurons_[i_neuron].setWeight(val, j_weight);
  }
}

void layer::setWeightDerivative(double val, int i_neuron, int j_weight) {
  if (i_neuron < 0 || j_weight < 0) {
    std::cout << "Error : you must use positive integers for this !\n";
    exit(1);
  }

  if (nb_neurons_ == 0 || i_neuron >= nb_neurons_ ||
      j_weight >= (arr_neurons_[i_neuron].getSizeX()) ||
      arr_neurons_ == nullptr) {
    std::cout << "Error : there isn't as many neurons or weights ! \n";
    exit(1);
  } else {
    arr_neurons_[i_neuron].setWeightDerivative(val, j_weight);
  }
}

void layer::setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                              int i_neuron, std::string name) {
  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integers for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    arr_neurons_[i_neuron].setActivationFcts(pf_a, pf_da, name);
  } else {
    std::cout << "Error : there isn't as many neurons in the layer !"
              << std::endl;
  }
}

void layer::setActivationFctName(std::string name, int i_neuron) {
  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    arr_neurons_[i_neuron].setActivationFctName(name);
  } else {
    std::cout << "Error : there isn't as many neurons in the layer !"
              << std::endl;
  }
}

std::ostream &operator<<(std::ostream &os, const layer &l) {
  os << "This layer is define with : \n"
     << "    An entry data vector of size : " << l.nb_data_ << "\n"
     << "    A number of neurons : " << l.nb_neurons_ << "\n";

  return os;
}

void layer::setBiais(double val, int i_neuron) {
  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    arr_neurons_[i_neuron].setBiais(val);
  } else {
    std::cout << "Error : there isn't as many neurons in the layer ! \n";
  }
}

void layer::setDb(double val, int i_neuron) {
  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    arr_neurons_[i_neuron].setDb(val);
  } else {
    std::cout << "Error : there isn't as many neurons in the layer ! \n";
  }
}

double layer::getBiais(int i_neuron) const {
  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  double res = 0;

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    res = arr_neurons_[i_neuron].getBiais();
  } else {
    std::cout << "Error : there isn't as many neurons in the layer ! \n";
  }

  return res;
}

double layer::getDb(int i_neuron) const {
  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  double res = 0;

  if (i_neuron < nb_neurons_ && nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    res = arr_neurons_[i_neuron].getDb();
  } else {
    std::cout << "Error : there isn't as many neurons in the layer ! \n";
  }

  return res;
}

bool layer::operator==(const layer &l) const {
  bool res = false;

  if (nb_neurons_ == l.nb_neurons_)
    res = true;

  return res;
}

bool layer::operator!=(const layer &l) const { return !(*this == l); }

bool layer::operator<=(const layer &l) const {
  bool res = false;

  if (nb_neurons_ <= l.nb_neurons_)
    res = true;

  return res;
}

void layer::addWeightDerivative(double val, int i_neuron, int j_weight) {
  if (i_neuron < 0 || j_weight < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && j_weight < arr_neurons_[i_neuron].getSizeX() &&
      arr_neurons_ != nullptr && nb_neurons_ != 0) {
    double w = getWeightDerivative(i_neuron, j_weight);
    setWeightDerivative(w + val, i_neuron, j_weight);
  }
}

void layer::setAllWeightsOnes() {
  if (nb_neurons_ != 0 && arr_neurons_ != nullptr) {

    for (int i = 0; i < nb_neurons_; ++i) {
      arr_neurons_[i].setWeightsOnes();
    }
  }
}

void layer::setAllWeightsRandoms() {
  if (nb_neurons_ != 0 && arr_neurons_ != nullptr) {
    for (int i = 0; i < nb_neurons_; ++i) {
      arr_neurons_[i].setWeightsRandom();
    }
  }
}

void layer::setAllWeightsDerivativesZeros() {
  if (nb_neurons_ != 0 && arr_neurons_ != nullptr) {

    for (int i = 0; i < nb_neurons_; ++i) {
      arr_neurons_[i].setWeightsDerivativesZeros();
    }
  }
}

double layer::evaluateFct(double x, int i_neuron) const {
  double res = 0;

  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && arr_neurons_ != nullptr && nb_neurons_ != 0)
    res = arr_neurons_[i_neuron].evaluateFct(x);

  return res;
}

double layer::evaluateFctDerivative(double x, int i_neuron) const {
  double res = 0;

  if (i_neuron < 0) {
    std::cout << "Error : you must use positive integer for this !\n";
    exit(1);
  }

  if (i_neuron < nb_neurons_ && arr_neurons_ != nullptr && nb_neurons_ != 0)
    res = arr_neurons_[i_neuron].evaluateFctDerivative(x);

  return res;
}

double *layer::evaluateLayer(const double *X, int size_X) const {
  if (size_X != nb_data_) {
    std::cout << "Error : this size of data isn't compatible with the layer !\n"
              << "    size required : " << getNbData()
              << ", size given : " << size_X << std::endl;
    exit(1);
  }

  for (int i = 0; i < nb_neurons_; ++i) {
    arr_neurons_[i].activateNeuron(X, size_X);
    Y_[i] = getPo(i);
  }

  return getY();
}

// this methods return the i-th neuron in the layer,
// the neuron is a reference not a copy
neuron &layer::operator()(int i_neuron) const {
  if (arr_neurons_ == nullptr || nb_neurons_ == 0 || i_neuron >= nb_neurons_) {
    std::cout << "Error : there isn't as many neurons in this layer \n";
    exit(1);
  }

  return arr_neurons_[i_neuron];
}