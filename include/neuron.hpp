#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <string>


class neuron {
  public:
    // default constructor
    neuron () {
        size_X_ = 0, po_ = 0.; biais_ = 0.; db_ = 0.;
        pf_activation_ = nullptr, pf_activation_d_ = nullptr, W_ = nullptr, dW_ = nullptr;
    }
    // construtor taking size of an entry vector 
    neuron (int n);
    // copy constructor
    neuron (const neuron & ne);
    // destructor
    ~neuron ();

    // getter setter
    int getSizeX () const;
    double getBiais () const;
    double getDb () const;
    double getW (int i) const;
    double getDW (int i)const;
    double getPo () const;
    void setBiais (double b);
    void setDb (double db);
    void setW (double w, int i);
    void setDW (double dw, int i);
    void setActivationFcts (double (*pf_a)(double), double (*pf_da)(double));
    void setActivationFctName (std::string sigma);

    // operator
    neuron operator= (const neuron &ne);                                     
    bool operator== (const neuron &ne) const;
    bool operator!= (const neuron &ne) const;
    friend std::ostream& operator<< (std::ostream& os, const neuron& ne);

    // methods
    void setWones ();
    void setWrandom (); // Unif([-1m, 1m]) distribution
    void setDWzeros ();
    void evaluation (const double *X);
    void printArr (const double *arr) const;

    // tests
    static int unitTest1 (); // tests constuctors 
    static int unitTest2 (); // tests getters setters 
    static int unitTest3 (); // tests operators and methods 

  private:
    int size_X_;
    double (*pf_activation_) (double);
    double (*pf_activation_d_) (double);
    double *W_;
    double *dW_;
    double po_;
    double biais_;
    double db_;
    std::string activation_fct_name_;
};


#endif