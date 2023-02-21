#include "../include/couche.hpp"
#include <iostream>



int couche:: unitTest1() {
    int passed = 0, total = 5;

    // default contructor
    couche c;
    if (c.m_nbNeurones == 0 && c.m_nbData == 0 && c.m_arrNeurones == nullptr )
        ++passed;
    //passed = 1
    // contructor taking size of data and nb of neurone 
    couche c1(2, 5); // X=(x,y) , 5 neurones
    if (c1.m_nbData == 2 && c1.m_nbNeurones == 5)
        ++passed;
    //passed = 2
    int k=0;
    for (int i=0; i<4; ++i) {
        if (c1.m_arrNeurones[i] == c1.m_arrNeurones[i+1])
            ++k;
    }
    if (k % 4 == 0) 
        ++passed;
    //passed = 3
    // copy constructor
    couche c2(c1);
    if (c1.m_nbNeurones == c2.m_nbNeurones && c1.m_nbData == c2.m_nbData && 
        c1.m_arrNeurones != c2.m_arrNeurones ) // last checks if pointers arent the same
        ++passed;
    //passed = 4
    k = 0;
    for (int i=0; i<c1.m_nbNeurones; ++i) {
        if (c1.m_arrNeurones[i] == c2.m_arrNeurones[i])
            ++k;
    }
    if (k % c1.m_nbNeurones == 0)
        ++passed;
    //passed = 5

    return passed % total;
} 



int main () {
    if (couche:: unitTest1() == 0)
        return 0;

    return 1;
}