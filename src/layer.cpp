#include "../include/layer.hpp"
#include "../include/neuron.hpp"

#include <iostream>

layer:: layer (const layer & co) {
    nb_neurons_ = co.nb_neurons_;
    nb_data_ = co.nb_data_;
    if (co.arr_neurons_ == nullptr) {
        arr_neurons_ = nullptr;   
    }
    else {
        arr_neurons_ = new neuron[nb_neurons_];
        for (int i=0; i<nb_neurons_; ++i)
            arr_neurons_[i] = co.arr_neurons_[i];
    }
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
        std::cout << "Error : there isn't as many neuron in the layer !" << std::endl;
    }    
    return res;
}
void layer:: setW (double val, int i, int j) {
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX()) {
        arr_neurons_[i].setW(val, j);
    }
    else {
        std::cout << "Error : there isn't as many neuron in the layer or as many weight in the neuron !" 
        << std::endl;
    }
}
void layer:: setDW (double val, int i, int j) {
    if (i < nb_neurons_ && j < arr_neurons_[i].getSizeX()) {
        arr_neurons_[i].setDW(val, j);
    }
    else {
        std::cout << "Error : there isn't as many neuron in the layer or as many weight in dW !" 
        << std::endl;
    }    
}
void layer:: setActivationFcts (double (*pf_a)(double), double (*pf_da)(double), int i) {// set to i-th neuron in the layer
    if (i < nb_neurons_) {
        arr_neurons_[i].setActivationFcts(pf_a, pf_da);
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer !" << std::endl;
    }
}
void layer:: setActivationFctName (std::string name, int i) {
    if (i < nb_neurons_) {
        arr_neurons_[i].setActivationFctName(name);
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer !" << std::endl;
    }
}
layer layer:: operator= (const layer &l) {
    if (this != &l) {
        nb_neurons_ = l.nb_neurons_;
        nb_data_ = l.nb_data_;
        if (arr_neurons_ != nullptr)
            delete [] arr_neurons_;
        if (l.arr_neurons_ == nullptr) {
            arr_neurons_ = nullptr;
        }
        else {
            arr_neurons_ = new neuron[nb_neurons_];
            for (int i=0; i<nb_neurons_; ++i)
                arr_neurons_[i] = l.arr_neurons_[i]; 
        }
    }
    return *this;
}
std::ostream& operator<< (std::ostream& os, const layer &l) {
    os << "This layer is define with : \n"
        << "    An entry data vector of size : " << l.nb_data_ << "\n"
        << "    A number of neurons : " << l.nb_neurons_ << "\n";

    return os;
}
void layer:: setBiais (double val, int i) {
    if (i < nb_neurons_) {
        arr_neurons_[i].setBiais(val);
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer ! \n";
    }
}
void layer:: setDb (double val, int i) {
    if (i < nb_neurons_) {
        arr_neurons_[i].setDb(val);
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer ! \n";
    }
}
double layer:: getBiais (int i) const {
    double res = 0;
    if (i < nb_neurons_) {
        res = arr_neurons_[i].getBiais();
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer ! \n";
    }
    return res;
}
double layer:: getDb (int i) const {
    double res = 0;
    if (i < nb_neurons_) {
        res = arr_neurons_[i].getBiais();
    }
    else {
        std::cout << "Error : there isn't as many neurons in the layer ! \n";
    }
    return res;
}
bool layer:: operator== (const layer &l) const {
    bool res = false;
    if (nb_neurons_ == l.nb_neurons_)
        res = true;
    return res;
}
bool layer:: operator!= (const layer &l) const {
    return !(*this == l);
}
bool layer:: operator< (const layer &l) const {
    bool res = false;
    if (nb_neurons_ < l.nb_neurons_)
        res = true;
    return res;
}

