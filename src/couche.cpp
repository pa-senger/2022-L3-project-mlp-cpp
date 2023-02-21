#include "../include/couche.hpp"
#include "../include/neurone.hpp"

#include <iostream>

couche:: couche (const couche & co) {
    nb_neurones_ = co.nb_neurones_;
    nb_data_ = co.nb_data_;
    arr_neurones_ = new neurone[nb_neurones_];
    for (int i=0; i<nb_neurones_; ++i)
        arr_neurones_[i] = co.arr_neurones_[i];
}
couche:: couche (int nb_data, int nb_ne) {
    nb_neurones_ = nb_ne;
    nb_data_ = nb_data;
    arr_neurones_ = new neurone[nb_ne];
    for (int i=0; i<nb_ne; ++i)
        arr_neurones_[i] = neurone(nb_data);
}
couche:: ~couche() {
    if (arr_neurones_ != nullptr)
        delete [] arr_neurones_;
}
double couche:: getW (int i, int j) const { // i-th neurone, j-th weight
    double res;
    if (i < nb_neurones_ && j < arr_neurones_[i].getSizeX())
        res = arr_neurones_[i].getW(j);
    return res;
}
double couche:: getDW (int i, int j) const { // i-th neurone, j-th derivative of W
    double res;
    if (i < nb_neurones_ && j < arr_neurones_[i].getSizeX())
        res = arr_neurones_[i].getDW(j);
    return res;  
}
int couche:: getNbData () const { return nb_data_; }
double couche:: getNbNeurones () const { return nb_neurones_; }
double couche:: getPo (int i) const { // get po of the i-th neurone
    double res = 0;
    if (i < nb_neurones_) {
        res = arr_neurones_[i].getPo();
    }
    else {
        std::cout << "Error : there is not as many neurone in the layer !" << std::endl;
    }    
    return res;
}
void couche:: setW (double val, int i, int j) {
    if (i < nb_neurones_ && j < arr_neurones_[i].getSizeX()) {
        arr_neurones_[i].setW(val, j);
    }
    else {
        std::cout << "Error : there is not as many neurone in the layer or as many weight in the neurone !" 
        << std::endl;
    }
}
void couche:: setDW (double val, int i, int j) {
    if (i < nb_neurones_ && j < arr_neurones_[i].getSizeX()) {
        arr_neurones_[i].setDW(val, j);
    }
    else {
        std::cout << "Error : there is not as many neurone in the layer or as many weight in dW !" 
        << std::endl;
    }    
}
