#include "../include/layer.hpp"
#include "../include/neuron.hpp"

#include <iostream>

layer:: layer (const layer & co) {
    nb_neurons_ = co.nb_neurons_;
    nb_data_ = co.nb_data_;
    arr_neurons_ = new neuron[nb_neurons_];
    for (int i=0; i<nb_neurons_; ++i)
        arr_neurons_[i] = co.arr_neurons_[i];
}
layer:: layer (int nb_data, int nb_ne) {
    nb_neurons_ = nb_ne;
    nb_data_ = nb_data;
    arr_neurons_ = new neuron[nb_ne];
    for (int i=0; i<nb_ne; ++i)
        arr_neurons_[i] = neuron(nb_data);
}
layer:: ~layer() {
    if (arr_neurons_ != nullptr)
        delete [] arr_neurons_;
}
double layer:: getW (int i, int j) const { // i-th neuron, j-th weight
    double res;
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX())
        res = arr_neurons_[i].getW(j);
    return res;
}
double layer:: getDW (int i, int j) const { // i-th neuron, j-th derivative of W
    double res;
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX())
        res = arr_neurons_[i].getDW(j);
    return res;  
}
int layer:: getNbData () const { return nb_data_; }
double layer:: getNbneurons () const { return nb_neurons_; }
double layer:: getPo (int i) const { // get po of the i-th neuron
    double res = 0;
    if (i < nb_neurons_) {
        res = arr_neurons_[i].getPo();
    }
    else {
        std::cout << "Error : there is not as many neuron in the layer !" << std::endl;
    }    
    return res;
}
void layer:: setW (double val, int i, int j) {
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX()) {
        arr_neurons_[i].setW(val, j);
    }
    else {
        std::cout << "Error : there is not as many neuron in the layer or as many weight in the neuron !" 
        << std::endl;
    }
}
void layer:: setDW (double val, int i, int j) {
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX()) {
        arr_neurons_[i].setDW(val, j);
    }
    else {
        std::cout << "Error : there is not as many neuron in the layer or as many weight in dW !" 
        << std::endl;
    }    
}
