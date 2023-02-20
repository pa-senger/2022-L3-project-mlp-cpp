#include "../include/neurone.hpp"
#include "../include/activ_functions.hpp"

#include <cmath>
#define TOL 1e-6



bool neurone:: unitTest2 () { // tests getters setters
    bool all_passed = false;
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


int main () {
    if (neurone:: unitTest2() == true)
        return 0;

    return 1;
}