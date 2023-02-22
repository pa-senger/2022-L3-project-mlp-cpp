#include "../include/neuron.hpp"
#include "../include/layer.hpp"
#include "../include/activation_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {
    double (*pf_s) (double) = &sigma;
    double (*pf_ds) (double) = &dSigma;

    neuron n(2, pf_s, pf_ds, "sigma");
   
    return 0;
}


