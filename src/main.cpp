#include "../include/neurone.hpp"
#include "../include/activ_functions.hpp"

#include <iostream>
#include <cmath>
#include <random>


int main() {

    neurone ne;
    ne.setWones();
    std::cout << ne.getSize() << std::endl;
    for (int i=0; i<10; ++i)
        std::cout << ne.getW(i) << " ; ";




    return 0;
}


