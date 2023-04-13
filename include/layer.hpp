#ifndef LAYER_HPP
#define LAYER_HPP
#include "neuron.hpp"
#include <cstddef>

class layer {
public:
  // * Constructors && Destructor && Affectation
  // This default constructor creates an empty layer
  layer() : nb_neurons_{0}, nb_data_{0}, arr_neurons_{nullptr}, Y_{nullptr} {}
  layer(const std::size_t nb_data, const std::size_t nb_neurons);
  layer(const layer &co);
  layer &operator=(const layer &l);
  ~layer();

  // * Getters && Setters
  inline std::size_t getNbData() const { return nb_data_; }
  inline std::size_t getNbNeurons() const { return nb_neurons_; }
  double getWeight(const std::size_t i_neuron,
                   const std::size_t j_weight) const;
  double getWeightDerivative(const std::size_t i_neuron,
                             const std::size_t j_weight) const;
  double getPo(const std::size_t i_neuron) const;
  double getBiais(const std::size_t i_neuron) const;
  double getDb(const std::size_t i_neuron) const;
  // Y is the array created by evaluating the layer
  inline double *getY() const { return Y_; }

  void setWeight(double val, const std::size_t i_neuron,
                 const std::size_t j_weight);
  void setWeightDerivative(double val, const std::size_t i_neuron,
                           const std::size_t j_weight);
  void setActivationFcts(double (*pf_a)(double), double (*pf_da)(double),
                         const std::size_t i_neuron, std::string name = "n/a");
  void setActivationFctName(std::string name, const std::size_t i_neuron);
  void setBiais(double val, const std::size_t i_neuron);
  void setDb(double val, const std::size_t i_neuron);

  // * Operators
  // 2 layers are equal if they have the same number of neurons
  bool operator==(const layer &l) const;
  bool operator!=(const layer &l) const;
  bool operator<=(const layer &l) const;
  // This () operator returns the object "neuron" as a reference not a copy
  neuron &operator()(const std::size_t i_neuron) const;
  friend std::ostream &operator<<(std::ostream &os, const layer &l);

  // * Other methods
  void addWeightDerivative(double val, const std::size_t i_neuron,
                           const std::size_t j_weight);
  // Those 3 next methods set weights to all of the neurons in the layer
  void setAllWeightsOnes();
  // Random weights are taken in the interval [a, b], ditribion : Unif([a, b])
  void setAllWeightsRandoms(int a, int b);
  void setAllWeightsDerivativesZeros();
  // This method returns the value of the activation fct given an entry x
  double evaluateFct(double x, const std::size_t i_neuron) const;
  double evaluateFctDerivative(double x, const std::size_t i_neuron) const;
  // This method evaluate the layer, ie activate each neuron,
  // each neuron takes X and return po the post_activation_value,
  // the method returns Y_ = (po_1,...,po_n)
  double *evaluateLayer(const double *X, const std::size_t size_X) const;
  void printY() const;

  // * Tests
  static void unitTest();

private:
  std::size_t nb_neurons_;
  std::size_t nb_data_; // The size of the entry vector of data
  neuron *arr_neurons_;
  double *Y_; // Array containing the values of the layer after activation.
  // We use Y_ because compiler isn't happy with us using dynamic array with
  // parameter size inside methods, which is kind of a problem to evaluate the
  // whole network.
  // This means there's a getter for Y_ that return the pointer, so be careful.
};

#endif