#ifndef LAYER_HPP
#define LAYER_HPP
#include "../include/neuron.hpp"


class layer {
  public:
    layer () : nb_neurons_(0), nb_data_(0), arr_neurons_(nullptr) {}
    layer (const layer & co);
    layer (int nb_data, int nb_ne);
    ~layer ();

    double getW (int i, int j) const; // i-th neuron, j-th weight
    double getDW (int i, int j) const; // i-th neuron, j-th derivative of W
    int getNbData () const;
    double getNbneurons () const;
    double getPo (int i) const; // get po of the i-th neuron
    void setW (double val, int i, int j);
    void setDW (double val, int i, int j);
    void setActivationFcts ();



    static int unitTest1(); // tests constructors
    static int unitTest2(); // tests getters setters

  private:
    int nb_neurons_;
    int nb_data_;
    neuron * arr_neurons_;
};




#endif