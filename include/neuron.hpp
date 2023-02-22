#ifndef NEURON_HPP
#define NEURON_HPP

#include "../include/activation_functions.hpp"

#include <iostream>
#include <string>


class neuron {
  public:
    // default constructor
    neuron () {
        size_X_ = 1, post_activation_value_ = 0.; biais_ = 0.; db_ = 0.;
        pf_activation_ = &ReLU;
        pf_activation_d_ = &dReLU;
        activation_fct_name_ = "ReLU";
        Weight_ = new double[1] {1};
        dWeight_ = new double[1] {0};
    }
    // construtor taking size of an entry vector 
    neuron (unsigned int n);
    // copy constructor
    neuron (const neuron &ne);
    // destructor
    ~neuron ();

    // getter setter
    int getSizeX () const;
    double getBiais () const;
    double getDb () const;
    double getWeight (unsigned int i) const;
    double getDWeight (unsigned int i)const;
    double getPo () const;

    void setBiais (double b);
    void setDb (double db);
    void setWeight (double Weight, unsigned int i);
    void setDWeight (double dWeight, unsigned int i);
    void setActivationFcts (double (*pf_a)(double), double (*pf_da)(double), std::string name = "n/a");
    void setActivationFctName (std::string name);

    // operator
    neuron operator= (const neuron &ne);                                     
    bool operator== (const neuron &ne) const;
    bool operator!= (const neuron &ne) const;
    friend std::ostream& operator<< (std::ostream& os, const neuron& ne);

    // methods
    void setWeightsOnes ();
    void setWeightsRandom (); // Unif([-1m, 1m]) distribution
    void setDWeightsZeros ();
    void activate (const double *X, unsigned int size);
    void printWeights (const double *arr) const;
    double evaluateFct (double x) const;
    double evaluateFctDerivative (double x) const;

    // tests
    static int unitTest1 (); // tests constuctors 
    static int unitTest2 (); // tests getters setters 
    static int unitTest3 (); // tests operators and methods 

  private:
    unsigned int size_X_;
    double (*pf_activation_) (double);
    double (*pf_activation_d_) (double);
    double *Weight_;
    double *dWeight_;
    double post_activation_value_;
    double biais_;
    double db_;
    std::string activation_fct_name_;
};


#endif