#include "../include/neurone.hpp"
#include "../include/activ_functions.hpp"

#include <cmath>
#include <iostream>


bool neurone:: unitTest3 () {
    bool all_passed = false;
    int passed = 0, total = 4;

    neurone ne(5);
    neurone ne2(10);

    // test setWOnes
    ne.setWones();
    int k = 0;
    for (int i=0; i<5; ++i) {
        if (ne.getW(i) == 1)
            ++k;
    }
    if (k % 5 == 0)
        ++passed;

    // test setWZeros
    ne.setDWzeros();
    k = 0;
    for (int i=0; i<5; ++i) {
        if (ne.getDW(i) == 0)
            ++k;
    }
    if (k % 5 == 0)
        ++passed;
    
    // test operator =
    // todo

    // test setWrandom
    ne2.setWrandom();
    ne = ne2;
    k = 0;
    for (int i=0; i<9; ++i) {
        if (ne2.getW(i) != ne2.getW(i+1))   
            ++k;
    }
    if (k % 9 == 0)
        ++passed;

    // test proper memory allocation
    ne2.setW(3, 0); 
    if (ne.getW(0) != ne2.getW(0))
        ++passed;
    

    if (passed % total == 0)    
        all_passed = true;
    return all_passed;
}


int main () {
    if (neurone:: unitTest3() == true)
        return 0;

    return 1;
}