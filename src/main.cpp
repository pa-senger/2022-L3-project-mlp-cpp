#include "../include/neuron.hpp"
#include "../include/layer.hpp"
#include "../include/activation_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {
    double (*pf_a) (double) = &sigma;
    double (*pf_da) (double) = &dSigma;

    neuron n(2, pf_a, pf_da, "sigma");
    layer l(2, 5);

    double X[2] {1,2};
    l.evaluateLayer(X, 2);
    double *Y = l.getY();

    for (int i=0; i<5; ++i)
        std::cout << Y[i] << " , ";
    std::cout << "\n";

    l.setActivationFcts(pf_a, pf_da, 4);
    l.setBiais(1.1, 0);
    l.setWeight(2.2, 4, 1);
    l.evaluateLayer(X, 2);
    double *Y2 = l.getY();

    for (int i=0; i<5; ++i)
        std::cout << Y2[i] << " , ";
    std::cout << "\n";
    std::cout << sigma(5.4) << std::endl;

    std::cout << l(4);
    
    return 0;
}


