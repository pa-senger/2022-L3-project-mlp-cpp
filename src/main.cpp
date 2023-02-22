#include "../include/neuron.hpp"
#include "../include/layer.hpp"
#include "../include/activation_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {

    layer l1(2, 3);
    l1.setAllWeightsOnes();
    l1.setAllDWeightsZeros();
    l1.setAllWeightsRandoms();

    neuron n;

    layer l2;

    std::cout << n;
    std::cout << l2;
   
    return 0;
}


