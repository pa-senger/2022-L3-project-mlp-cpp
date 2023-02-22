#include "../include/neuron.hpp"
#include "../include/activation_functions.hpp"

#include <cmath>
#include <iostream>

#define TOL 1e-6

double (*pf_s) (double) = &sigma;
double (*pf_ds) (double) = &dSigma;

int neuron:: unitTest1 () { // tests constuctors 
    int passed = 0;

    neuron n;
    neuron n1(5);
    neuron n2(n1);

    // default constructor
    if (n.size_X_ == 1 && n.post_activation_value_ == 0. && 
        n.pf_activation_ == &ReLU && n.pf_activation_d_ == &dReLU && n.Weight_[0] == 1 
        && n.Weight_d_[0] == 0 && n.Weight_[1] == 0 && n.Weight_d_[1] == 0
        && n1.pre_activation_value_ == 0. )
        ++passed; 
    //passed = 1
    // constructor taking the size of X
    if (n1.size_X_ == 5 && n1.post_activation_value_ == 0. && n1.pf_activation_ == &ReLU && 
        n1.pf_activation_d_ == &dReLU && n1.pre_activation_value_ == 0.)
        ++passed;
    //passed = 2    
    int k = 0;
    for (int i=0; i<n1.size_X_; ++i) {
        if (n1.Weight_[i] == 1 && n1.Weight_d_[i] == 0)   
            ++k;
    }
    if (k % n1.size_X_ == 0)
        ++passed;    
    //passed = 3

    // copy constructor
    if (n2.size_X_ == n1.size_X_ && n2.post_activation_value_ == n1.post_activation_value_ 
        && n2.pf_activation_ == n1.pf_activation_ 
        && n2.pf_activation_d_ == n1.pf_activation_d_ )
        ++passed;
    //passed = 4
    k = 0;
    for (int i=0; i<(n1.size_X_+1); ++i) {
        if (n2.Weight_[i] == n1.Weight_[i] && n2.Weight_d_[i] == n1.Weight_d_[i])   
            ++k;
    }
    if (k % (n2.size_X_+1) == 0)
        ++passed;
    //passed = 5
    neuron n3(2, pf_s, pf_ds, "sigma");
    if (n3.size_X_ == 2 && n3.post_activation_value_ == 0  && 
        n3.pf_activation_ == &sigma && n3.pf_activation_d_ == &dSigma )
        ++passed;
    //passed =6

    return passed % 6; // return 0 if all successful
}

int neuron:: unitTest2 () { // tests getters setters
    int passed = 0;

    neuron n(10);
    n.setWeight(1.1, 9);
    n.setDWeight(2.2, 0);
    n.setBiais(3.3);
    n.setDb(4.4);
    n.setActivationFcts(pf_s, pf_ds);

    if (n.getWeight(9) == 1.1 && n.getDWeight(0) == 2.2 && n.getBiais() == 3.3 
        && n.getDb() == 4.4 && n.getPo() == 0. && n.getSizeX() == 10)
        ++passed;
    //passed = 1;
    if (n.pf_activation_ == pf_s)
        ++passed;
    //passed = 2   
    if (n.pf_activation_(2.2) - pf_s(2.2) <= TOL)  // sigma(2.2) ~= 0.90024  
        ++passed;
    //passed = 3
    if (n.pf_activation_d_ == pf_ds)
        ++passed;
    //passed = 4
    if (n.pf_activation_d_(2.2) - pf_ds(2.2) <= TOL)  // dSigma(2.2) ~= 0.109459 
        ++passed;  
    //passed = 5

    return passed % 5;
}

int neuron:: unitTest3 () {
    int passed = 0;

    neuron ne(5);
    neuron ne1(6);
    neuron ne2(10);

    // test setWeightOnes
    ne.setWeightsOnes();
    int k = 0;
    for (int i=0; i<5; ++i) {
        if (ne.getWeight(i) == 1)
            ++k;
    }
    if (k % 5 == 0)
        ++passed;
    //passed = 1
    // test setWeightZeros
    ne.setDWeightsZeros();
    k = 0;
    for (int i=0; i<5; ++i) {
        if (ne.getDWeight(i) == 0)
            ++k;
    }
    if (k % 5 == 0)
        ++passed;
    //passed = 2
    // test operator =
    ne1.setWeightsOnes();
    ne1 = ne2;
    if (ne2.size_X_ == ne1.size_X_ && ne2.post_activation_value_ == ne1.post_activation_value_ 
        && ne2.getBiais() == ne1.getBiais() && ne2.getDb() == ne1.getDb()
        && ne2.pf_activation_ == ne1.pf_activation_ 
        && ne2.pf_activation_d_ == ne1.pf_activation_d_ )
        ++passed;
    //passed = 3
    k = 0;
    for (int i=0; i<ne1.size_X_+1; ++i) {
        if (ne2.Weight_[i] == ne1.Weight_[i] && ne2.Weight_d_[i] == ne1.Weight_d_[i])   
            ++k;
    }
    if (k % (ne2.size_X_+1) == 0)
        ++passed;
    //passed = 4
    // test proper memory allocation
    ne2.setWeight(4, 0); 
    if (ne1.getWeight(0) != ne2.getWeight(0))
        ++passed;
    //passed = 5
    // test setWeightrandom
    ne2.setWeightsRandom();
    ne = ne2;
    k = 0;
    for (int i=0; i<9; ++i) {
        if (ne2.getWeight(i) != ne2.getWeight(i+1))   
            ++k;
    }
    if (k % 9 == 0)
        ++passed;
    //passed = 6
    // test proper memory allocation
    ne2.setWeight(3, 0); 
    if (ne.getWeight(0) != ne2.getWeight(0))
        ++passed;
    //passed = 7
    // test activate
    neuron ne3(4);
    for (int i=0; i<4; ++i) {
        ne3.setWeight(i+1, i);
    }
    double X[4] = {.1, .2, .3, .4};
    double biais = .2;
    ne3.setBiais(biais);
    ne3.setActivationFcts(pf_s, pf_ds);
    ne3.activateNeuron(X, 4);
    if (ne3.getPo() == sigma(3.2))  
        ++passed;
    //passed = 8
    // test operator ==
    neuron neu1(4);
    neuron neu2(4);
    neuron neu3;
    if ( (neu1==neu3) == false && (neu1==neu2) == true )
        ++passed;
    //passed = 9
    neu1.setWeightsOnes();
    neu2.setWeightsOnes();
    if ( (neu1==neu2) == true)
        ++passed;
    //passed = 10
    neu1.setBiais(1) ; neu2.setBiais(1);
    neu1.setActivationFcts(pf_s, pf_ds); neu2.setActivationFcts(pf_s, pf_ds);
    neu1.setWeight(4.1, 2); neu2.setWeight(4.1, 2);
    neu1.setDWeight(3.1, 2); neu2.setDWeight(3.1, 2);
    neu1.activateNeuron(X, 4); neu2.activateNeuron(X, 4);
    if ( (neu1==neu2) == true)
        ++passed;
    //passed = 11
    neu1.setWeight(5.2, 0);
    if ( (neu1==neu2) == false)
        ++passed;
    //passed = 12
    if ( (neu1!=neu2) == true )
        ++passed;
    //passed = 13
    if (ne3.evaluateFct(5) == sigma(5) && ne3.evaluateFctDerivative(1.1) == dSigma(1.1))
        ++passed;
    //passed = 14

    return passed % 14;
}


int main () {

    return (neuron::unitTest1() + neuron::unitTest2() + neuron::unitTest3());
}