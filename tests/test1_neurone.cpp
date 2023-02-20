#include "../include/neurone.hpp"
#include "../include/activ_functions.hpp"

#include <cmath>
#include <iostream>


bool neurone:: unitTest1 () { // tests constuctors 
    bool all_passed = false;
    int passed = 0, total = 5;

    neurone n;
    neurone n1(5);
    neurone n2(n1);

    // default constructor
    if (n.m_size == 0 && n.m_po == 0. && n.m_biais == 0. && n.m_db == 0. 
        && n.pfSigma == nullptr && n.pfDsigma == nullptr && n.m_W == nullptr && n.m_dW == nullptr)
        ++passed;    

    // constructor taking the size of X
    if (n1.m_size == 5 && n1.m_po == 0. && n1.m_biais == 0. && n1.m_db == 0. &&
        n1.pfSigma == nullptr && n1.pfDsigma == nullptr && n1.m_W != nullptr && n1.m_dW != nullptr)
        ++passed;
    int k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n1.m_W[i] == 0. && n1.m_dW[i] == 0.)   
            ++k;
    }
    if (k % n1.m_size == 0)
        ++passed;    

    // copy constructor
    if (n2.m_size == n1.m_size && n2.m_po == n1.m_po && n2.m_biais == n1.m_biais &&
        n2.m_db == n1.m_db && n2.pfSigma == n1.pfSigma && n2.pfDsigma == n1.pfDsigma )
        ++passed;
    k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n2.m_W[i] == n1.m_W[i] && n2.m_dW[i] == n1.m_dW[i])   
            ++k;
    }
    if (k % n2.m_size == 0)
        ++passed;

    // results
    if (passed % total == 0)    
        all_passed = true; // true = 1
    return all_passed;
}

int main () {
    if (neurone:: unitTest1() == true)
        return 0;

    return 1;
}