#ifndef LAYER_HPP
#define LAYER_HPP
#include "neuron.hpp"

class layer {
public:
  // this default constructor creates an empty layer
  layer() : nb_neurons_{0}, nb_data_{0}, arr_neurons_{nullptr}, Y_{nullptr} {}
  layer(int nb_data, int nb_neurons);
  layer(const layer &co);
  ~layer();

  double getWeight(int i_neuron, int j_weight) const;
  double getWeightDerivative(int i_neuron, int j_weight) const;
  int getNbData() const;
  double getNbNeurons() const;
  double getPo(int i_neuron) const;
  double getBiais(int i_neuron) const;
  double getDb(int i_neuron) const;

  // Y is the vector created by evaluating the layer
  double *getY() const { return Y_; }

  void setWeight(double val, int i_neuron, int j_weight);
  void setWeightDerivative(double val, int i_neuron, int j_weight);
  void setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                         int i_neuron, std::string name = "n/a");
  void setActivationFctName(std::string name, int i_neuron);
  void setBiais(double val, int i_neuron);
  void setDb(double val, int i_neuron);

  layer &operator=(const layer &l);

  // 2 layers are equal if they have the same number of neurons
  bool operator==(const layer &l) const;
  bool operator!=(const layer &l) const;
  bool operator<=(const layer &l) const;

  // this () operator returns the object "neuron" as a reference not a copy
  neuron &operator()(int i_neuron) const;

  friend std::ostream &operator<<(std::ostream &os, const layer &l);

  void addWeightDerivative(double val, int i_neuron, int j_weight);

  // those 3 methods sets weights to all of the neurons in the layer
  void setAllWeightsOnes();
  void setAllWeightsRandoms();
  void setAllWeightsDerivativesZeros();

  // this method returns the value of the activation fct given an entry x
  double evaluateFct(double x, int i_neuron) const;
  double evaluateFctDerivative(double x, int i_neuron) const;

  // this method evaluate the layer, ie activate each neuron
  // each neuron takes X and return po the post_activation_value
  // the method returns an array Y = (po_1,...,po_n)
  double *evaluateLayer(const double *X, int size_X) const;

  static int unitTest1(); // tests constructors
  static int unitTest2(); // tests getters setters
  static int unitTest3(); // tests operators
  static int unitTest4(); // tests the rest of the methods

private:
  int nb_neurons_;
  int nb_data_;         // the size of the entry vector of data
  neuron *arr_neurons_; // an array of neurons
  double *Y_; // array containing the values of the layer after activation
};

#endif