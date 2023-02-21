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






    return 0;
}


