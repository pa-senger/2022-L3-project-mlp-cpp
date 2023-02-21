#include "../include/couche.hpp"
#include <iostream>



int couche:: unitTest1() {
    int passed = 0, total = 5;

    // default contructor
    couche c;
    if (c.nb_neurones_ == 0 && c.nb_data_ == 0 && c.arr_neurones_ == nullptr )
        ++passed;
    //passed = 1
    // contructor taking size of data and nb of neurone 
    couche c1(2, 5); // X=(x,y) , 5 neurones
    if (c1.nb_data_ == 2 && c1.nb_neurones_ == 5)
        ++passed;
    //passed = 2
    int k=0;
    for (int i=0; i<4; ++i) {
        if (c1.arr_neurones_[i] == c1.arr_neurones_[i+1])
            ++k;
    }
    if (k % 4 == 0) 
        ++passed;
    //passed = 3
    // copy constructor
    couche c2(c1);
    if (c1.nb_neurones_ == c2.nb_neurones_ && c1.nb_data_ == c2.nb_data_ && 
        c1.arr_neurones_ != c2.arr_neurones_ ) // last checks if pointers arent the same
        ++passed;
    //passed = 4
    k = 0;
    for (int i=0; i<c1.nb_neurones_; ++i) {
        if (c1.arr_neurones_[i] == c2.arr_neurones_[i])
            ++k;
    }
    if (k % c1.nb_neurones_ == 0)
        ++passed;
    //passed = 5

    return passed % total;
} 
int couche:: unitTest2() { // tests getters setters
    int passed = 0, total = 1;

    return passed % total;
}

int main () {
    if (couche:: unitTest1() == 0)
        return 0;

    return 1;
}