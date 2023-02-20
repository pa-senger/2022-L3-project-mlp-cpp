#include "../include/neurone.hpp"
#include <cmath>
#define TOL 1e-6


double sigma (double x) {
    double res;
    res = (1. / (1 + exp(-x)));
    return res;
}
double dSigma (double x) {
    double res;
    res = (double) exp(-x) / (1 + exp(-x) * (1 + exp(-x)));
    return res;
}
bool neurone:: unitTest1 () { // tests constuctor 
    bool all_passed = false;
    int passed = 0, total = 6;

    neurone n;
    neurone n1(5);
    neurone n2(n1);

    // default constructor
    if (n.m_size == 0. && n.m_po == 0. && n.m_biais == 0. && n.m_db == 0. &&
        n.pfSigma == nullptr && n.pfDsigma == nullptr && n.m_W == nullptr && n.m_dW == nullptr)
        ++passed;
    int k = 0;
    for (int i=0; i<n.m_size; ++i) {
        if (n.m_W[i] == 0. && n.m_dW[i] == 0.)   
            ++k;
    }
    if (k % n.m_size == 0)
        ++passed;   

    // constructor taking the size of X
    if (n1.m_size == 5 && n1.m_po == 0. && n1.m_biais == 0. && n1.m_db == 0. &&
        n1.pfSigma == nullptr && n1.pfDsigma == nullptr && n1.m_W != nullptr && n1.m_dW != nullptr)
        ++passed;
    k = 0;
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

    // result
    if (passed % total == 0)    
        all_passed = true; // true = 1
    return all_passed;
}
bool neurone:: unitTest2 () { // tests getters setters
    bool all_passed = false;
    int passed = 0, total = 5;

    neurone n(10);
    n.setW(1.1, 10);
    n.setDw(2.2, 0);
    n.setBiais(3.3);
    n.setDb(4.4);
    double (*pfS) (double) = &sigma;
    n.setSigma(pfS);
    double (*pfDs) (double) = &dSigma;
    n.setDsigma(pfDs);

    if (n.getW(10) == 1.1 && n.getDw(0) == 2.2 && n.getBiais() == 3.3 && n.getDb() == 4.4 && 
        n.getPo() == 0. )
        ++passed;
    if (n.pfSigma == pfS)
        ++passed;
    if (n.pfSigma(2.2) - pfS(2.2) <= TOL)  // sigma(2.2) ~= 0.90024  
        ++passed;
    if (n.pfDsigma == pfDs)
        ++passed;
    if (n.pfDsigma(2.2) - pfDs(2.2) <= TOL)  // dSigma(2.2) ~= 0.109459 
        ++passed;  

    if (passed % total == 0)    
        all_passed = true;
    return all_passed;
}

