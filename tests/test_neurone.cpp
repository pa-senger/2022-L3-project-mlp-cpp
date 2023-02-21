#include "../include/neurone.hpp"
#include "../include/activ_functions.hpp"

#include <cmath>
#include <iostream>
#define TOL 1e-6


int neurone:: unitTest1 () { // tests constuctors 
    int passed = 0, total = 5;

    neurone n;
    neurone n1(5);
    neurone n2(n1);

    // default constructor
    if (n.m_size == 0 && n.m_po == 0. && n.m_biais == 0. && n.m_db == 0. 
        && n.pfSigma == nullptr && n.pfDsigma == nullptr && n.m_W == nullptr && n.m_dW == nullptr)
        ++passed;    
    //passed = 1
    // constructor taking the size of X
    if (n1.m_size == 5 && n1.m_po == 0. && n1.m_biais == 0. && n1.m_db == 0. &&
        n1.pfSigma == nullptr && n1.pfDsigma == nullptr && n1.m_W != nullptr && n1.m_dW != nullptr)
        ++passed;
    //passed = 2    
    int k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n1.m_W[i] == 0. && n1.m_dW[i] == 0.)   
            ++k;
    }
    if (k % n1.m_size == 0)
        ++passed;    
    //passed = 3
    // copy constructor
    if (n2.m_size == n1.m_size && n2.m_po == n1.m_po && n2.m_biais == n1.m_biais &&
        n2.m_db == n1.m_db && n2.pfSigma == n1.pfSigma && n2.pfDsigma == n1.pfDsigma )
        ++passed;
    //passed = 4
    k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n2.m_W[i] == n1.m_W[i] && n2.m_dW[i] == n1.m_dW[i])   
            ++k;
    }
    if (k % n2.m_size == 0)
        ++passed;
    //passed = 5

    return passed % total; // return 0 if all succesful
}

int neurone:: unitTest2 () { // tests getters setters
    int passed = 0, total = 5;

    neurone n(10);
    n.setW(1.1, 10);
    n.setDW(2.2, 0);
    n.setBiais(3.3);
    n.setDb(4.4);
    double (*pfS) (double) = &sigma;
    n.setSigma(pfS);
    double (*pfDs) (double) = &dSigma;
    n.setDsigma(pfDs);

    if (n.getW(10) == 1.1 && n.getDW(0) == 2.2 && n.getBiais() == 3.3 && n.getDb() == 4.4 && 
        n.getPo() == 0. )
        ++passed;
    //passed = 1;
    if (n.pfSigma == pfS)
        ++passed;
    //passed = 2    
    if (n.pfSigma(2.2) - pfS(2.2) <= TOL)  // sigma(2.2) ~= 0.90024  
        ++passed;
    //passed = 3
    if (n.pfDsigma == pfDs)
        ++passed;
    //passed = 4
    if (n.pfDsigma(2.2) - pfDs(2.2) <= TOL)  // dSigma(2.2) ~= 0.109459 
        ++passed;  
    //passed = 5

    return passed % total;
}

int neurone:: unitTest3 () {
    int passed = 0, total = 13;

    neurone ne(5);
    neurone ne1(6);
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
    //passed = 1
    // test setWZeros
    ne.setDWzeros();
    k = 0;
    for (int i=0; i<5; ++i) {
        if (ne.getDW(i) == 0)
            ++k;
    }
    if (k % 5 == 0)
        ++passed;
    //passed = 2
    // test operator =
    ne1.setWones();
    ne1 = ne2;
    if (ne2.m_size == ne1.m_size && ne2.m_po == ne1.m_po && ne2.m_biais == ne1.m_biais &&
        ne2.m_db == ne1.m_db && ne2.pfSigma == ne1.pfSigma && ne2.pfDsigma == ne1.pfDsigma )
        ++passed;
    //passed = 3
    k = 0;
    for (int i=0; i<ne1.m_size; ++i) {
        if (ne2.m_W[i] == ne1.m_W[i] && ne2.m_dW[i] == ne1.m_dW[i])   
            ++k;
    }
    if (k % ne2.m_size == 0)
        ++passed;
    //passed = 4
    // test proper memory allocation
    ne2.setW(4, 0); 
    if (ne1.getW(0) != ne2.getW(0))
        ++passed;
    //passed = 5
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
    //passed = 6
    // test proper memory allocation
    ne2.setW(3, 0); 
    if (ne.getW(0) != ne2.getW(0))
        ++passed;
    //passed = 7
    // test evaluation
    neurone ne3(4);
    for (int i=0; i<4; ++i) {
        ne3.setW(i+1, i);
    }
    double X[4] = {.1, .2, .3, .4};
    double biais = .2;
    ne3.setBiais(biais);
    double (*pfS) (double) = &sigma;
    ne3.setSigma(pfS);
    ne3.evaluation(X);
    if (ne3.getPo() == sigma(3.2))  
        ++passed;
    //passed = 8
    // test operator ==
    neurone neu1(4);
    neurone neu2(4);
    neurone neu3;
    if ( (neu1==neu3) == false && (neu1==neu2) == true )
        ++passed;
    //passed = 9
    neu1.setWones();
    neu2.setWones();
    if ( (neu1==neu2) == true)
        ++passed;
    //passed = 10
    neu1.setBiais(1) ; neu2.setBiais(1);
    neu1.setSigma(pfS); neu2.setSigma(pfS);
    neu1.setW(4.1, 2); neu2.setW(4.1, 2);
    neu1.setDW(3.1, 2); neu2.setDW(3.1, 2);
    neu1.evaluation(X); neu2.evaluation(X);
    if ( (neu1==neu2) == true)
        ++passed;
    //passed = 11
    neu1.setW(5.2, 0);
    if ( (neu1==neu2) == false)
        ++passed;
    //passed = 12
    if ( (neu1!=neu2) == true )
        ++passed;
    //passed = 13

    return passed % total;
}


int main () {
    if (neurone:: unitTest1() == 0 && neurone:: unitTest2() == 0 &&
        neurone:: unitTest3() == 0)
        return 0;

    return 1;
}