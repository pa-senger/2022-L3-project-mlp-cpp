#include "../include/layer.hpp"
#include "../include/activation_functions.hpp"
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
    int passed = 0, total = 2;

    layer l1;
    layer l2(2, 5); // X=(x,y) , 5 neurons (0..4)
    layer l3(2, 3);
    l2.setW(1.1, 4, 1); // 4th neuron, 1st weight
    l2.setDW(2.2, 0, 0);
    double (*pf_a)(double) = &sigma;
    double (*pf_da)(double) = &dSigma;
    l2.setActivationFcts(pf_a, pf_da, 4);
    l2.setActivationFctName("sigma", 4);
    l2.setBiais(4.4, 0);
    l2.setDb(5.5, 4);
    if (l2.getNbData() == 2 && l2.getNbneurons() == 5 && l2.getW(4, 1) == 1.1 &&
        l2.getDW(0, 0) == 2.2 && l2.getBiais(0) == 4.4 && l2.getDb(4) == 5.5)
        ++passed;
    // passed = 1;
    l3.setW(0.1, 1, 1); // value, neuron , W index
    l3.setW(0.2, 1, 1);
    l3.setBiais(0.3, 1); // value, neuron index in the layer
    l3.setActivationFcts(pf_a, pf_da, 1);
    double X[2] = {1, 2};
    l3.arr_neurons_[1].evaluation(X);
    if ( l3.arr_neurons_[1].getPo() == pf_a(0.8))
        ++passed;
std::cout << l3.arr_neurons_[1].getPo() << std::endl;
    // passed = 2

    return passed % total;
}

int main () {
    if (layer:: unitTest1() == 0 and layer:: unitTest2() == 0)
        return 0;

    return 1;
}