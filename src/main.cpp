#include "../include/neurone.hpp"
#include "../include/couche.hpp"
#include "../include/activ_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {


    couche c1(2, 5);

    std::cout << c1.getDW(4, 1) << std::endl;  

    c1.setDW(3.2, 4, 1);
    
    std::cout << c1.getDW(4, 1) << std::endl;  

    neurone n1(5);
    
    n1.setActivFctName("sigma");
    std::cout << n1;






    return 0;
}


