#ifndef LAYER_HPP
#define LAYER_HPP
#include "../include/neuron.hpp"


class layer {
  public:
    layer () : nb_neurons_(0), nb_data_(0), arr_neurons_(nullptr) {} // empty layer
    layer (const layer & co);
    layer (int nb_data, int nb_ne);
    ~layer ();

    double getWeight (int i, int j) const; // i-th neuron, j-th Weight
    double getDWeight (int i, int j) const; // i-th neuron, j-th derivative of Weight
    int getNbData () const;
    double getNbNeurons () const;
    double getPo (int i) const; // get post activation value of the i-th neuron
    double getBiais (int i) const;
    double getDb (int i) const;

    void setWeight (double val, int i, int j);
    void setDWeight (double val, int i, int j);
    void setActivationFcts (double (*pf_a)(double), double (*pf_da)(double), int i); // set to i-th neuron in the layer
    void setActivationFctName (std::string name, int i);
    void setBiais (double val, int i);
    void setDb (double val, int i);

    layer operator= (const layer &l);
    bool operator== (const layer &l) const;
    bool operator!= (const layer &l) const;
    bool operator<= (const layer &l) const;
    friend std::ostream& operator<< (std::ostream &os, const layer &l);

    void addDWeight (double val, int i, int j); // i-th neuron, j-th Weight
    void setAllWeightsOnes ();
    void setAllWeightsRandoms ();
    void setAllDWeightsZeros ();
    double evaluateFct(double x, int i) const; // evaluateFct(double) of the i-th neuron
    double evaluateFctDerivative(double x, int i) const; 


    static int unitTest1(); // tests constructors
    static int unitTest2(); // tests getters setters
    static int unitTest3(); // tests operators
    static int unitTest4(); // tests the rest of the methods

  private:
    int nb_neurons_;
    int nb_data_;
    neuron * arr_neurons_;
};




#endif