#include "../include/layer.hpp"
#include <iostream>


int layer:: unitTest1() {
    int passed = 0, total = 5;

    // default contructor
    layer c;
    if (c.nb_neurons_ == 0 && c.nb_data_ == 0 && c.arr_neurons_ == nullptr )
        ++passed;
    //passed = 1
    // contructor taking size of data and nb of neuron 
    layer c1(2, 5); // X=(x,y) , 5 neurons
    if (c1.nb_data_ == 2 && c1.nb_neurons_ == 5)
        ++passed;
    //passed = 2
    int k=0;
    for (int i=0; i<4; ++i) {
        if (c1.arr_neurons_[i] == c1.arr_neurons_[i+1])
            ++k;
    }
    if (k % 4 == 0) 
        ++passed;
    //passed = 3
    // copy constructor
    layer c2(c1);
    if (c1.nb_neurons_ == c2.nb_neurons_ && c1.nb_data_ == c2.nb_data_ && 
        c1.arr_neurons_ != c2.arr_neurons_ ) // last checks if pointers arent the same
        ++passed;
    //passed = 4
    k = 0;
    for (int i=0; i<c1.nb_neurons_; ++i) {
        if (c1.arr_neurons_[i] == c2.arr_neurons_[i])
            ++k;
    }
    if (k % c1.nb_neurons_ == 0)
        ++passed;
    //passed = 5

    return passed % total;
} 
int layer:: unitTest2() { // tests getters setters
    int passed = 0, total = 1;

    return passed % total;
}

int main () {
    if (layer:: unitTest1() == 0)
        return 0;

    return 1;
}