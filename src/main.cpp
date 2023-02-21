#include "../include/neuron.hpp"
#include "../include/layer.hpp"
#include "../include/activation_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {


    layer c1(2, 5);

    std::cout << c1.getDW(4, 1) << std::endl;  

    c1.setDW(3.2, 4, 1);
    
    std::cout << c1.getDW(4, 1) << std::endl;  

    neuron n1(5);
    
    n1.setActivationFctName("sigma");
    std::cout << n1;

    double (*pf_a)(double) = &sigma;
    double (*pf_da)(double) = &dSigma;
    c1.setActivationFcts(pf_a, pf_da, 4);

    double *arr = new double[0];
    std::cout << arr << std::endl;

    double *p = nullptr;
    std::cout << p << std::endl;

    neuron n2;
    neuron n3(n2);

    std::cout << n3 ;
     






    return 0;
}


