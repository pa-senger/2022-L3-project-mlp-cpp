#include "../include/neuron.hpp"
#include <iostream>
#include <cmath>
#include <random>


neuron:: neuron (int n) {
    size_X_ = n;
    po_ = 0.;
    biais_ = 0.;
    db_ = 0.;
    pf_activation_ = nullptr;
    pf_activation_d_ = nullptr;
    if (n == 0) {
        W_ = nullptr;
        dW_ = nullptr;
    }
    else {
        W_ = new double [n];
        dW_ = new double [n];
        for (int i=0; i<n; ++i) {
            W_[i] = 0.;
            dW_[i] = 0.;
        }
    }
}
neuron:: neuron (const neuron &ne) {
    size_X_ = ne.size_X_;
    po_ = ne.po_;
    biais_ = ne.biais_;
    db_ = ne.db_;
    pf_activation_ = ne.pf_activation_; // pointer to the same "object"
    pf_activation_d_ = ne.pf_activation_d_; // functions arent object so they cant be deep copied
    if (size_X_ == 0) {
        W_ = nullptr;
        dW_ = nullptr;
    }
    else {
        W_ = new double [size_X_];
        dW_ = new double [size_X_];
        for (int i=0; i<size_X_; ++i) {
            W_[i] = ne.W_[i];
            dW_[i] = ne.dW_[i];
        }
    }
} 
neuron:: ~neuron () { 
    if ( W_ != nullptr)
        delete [] W_;
    if ( dW_ != nullptr)
        delete [] dW_;    
}
int neuron:: getSizeX () const { return size_X_; }
double neuron:: getBiais () const { return biais_; }
double neuron:: getDb () const { return db_; }
double neuron:: getW (int i) const { return W_[i]; }
double neuron:: getDW (int i) const { return dW_[i] ; }
double neuron:: getPo () const { return po_; }
void neuron:: setBiais (double b) { biais_ = b; }
void neuron:: setDb (double db) { db_ = db; }
void neuron:: setW (double w, int i) { W_[i] = w; }
void neuron:: setDW (double dw, int i) { dW_[i] = dw; }
void neuron:: setActivationFcts (double (*pf_a)(double), double (*pf_da)(double)) {
    pf_activation_ = pf_a;
    pf_activation_d_ = pf_da;
}
neuron neuron:: operator= (const neuron &ne) {
    if ( this != &ne ) {
        size_X_ = ne.size_X_;
        po_ = ne.po_;
        biais_ = ne.biais_;
        db_ = ne.db_;
        pf_activation_ = ne.pf_activation_;
        pf_activation_d_ = ne.pf_activation_d_;
        if (W_ != nullptr) {
            delete [] W_;
        }
        if (dW_ != nullptr) {
            delete [] dW_;
        }
        if (size_X_ == 0) {
            W_ = nullptr;
            dW_ = nullptr;
        }
        else {
            W_ = new double [size_X_];
            dW_ = new double [size_X_];
            for (int i=0; i<size_X_; ++i) {
                W_[i] = ne.W_[i];
                dW_[i] = ne.dW_[i];
            }
        }   
    }
    return *this;
}
void neuron:: setWones () {
    if ( W_ != nullptr ) {
       delete [] W_;
    }
    W_ = new double [size_X_];   
    for (int i=0; i<size_X_; ++i) {
        W_[i] = 1.;
    }
}
void neuron:: setDWzeros () {
    if ( dW_ != nullptr ) {
       delete [] dW_;
    }
    dW_ = new double [size_X_];   
    for (int i=0; i<size_X_; ++i) {
        dW_[i] = 0.;
    }
}
void neuron:: setWrandom () {
    std::random_device rd;
    std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(-1'000'000, 1'000'000);
    for (int i=0; i<size_X_; ++i) 
        W_[i] = dis(gen);
}
void neuron:: evaluation (const double *X) {
    double dot = 0;
    for (int i=0; i<size_X_; ++i) {
        dot += (W_[i] * X[i]);
    }
    po_ = pf_activation_(dot + biais_);
}
bool neuron:: operator== (const neuron &ne) const {
    bool res = true;
    if(size_X_ != ne.size_X_ || pf_activation_ != ne.pf_activation_ || pf_activation_d_ != ne.pf_activation_d_ ||
        po_ != ne.po_ || biais_ != ne.biais_ || db_ != ne.db_)
        return false;
    for (int i=0; i<size_X_; ++i) {
        if (W_[i] != ne.W_[i] || dW_[i] != ne.dW_[i])
        return false;
    }
    return res;
}
bool neuron:: operator!= (const neuron &ne) const {
    return !( *this == ne);
}
void neuron:: printArr (const double *arr) const {
    if ( arr != nullptr) {
        std::cout << "[";
        for (int i=0; i<size_X_-1; ++i) {
            std::cout << arr[i] << ", ";
        }
        std::cout << arr[size_X_-1] << "] \n";
    }
    else {
        std::cout << "the array is empty \n";
    }

}
void neuron:: setActivationFctName (std::string sigma) {
    activation_fct_name_ = sigma;
}

std::ostream& operator<< (std::ostream& os, const neuron& ne) {
    os << "This neuron is define with : \n"
        << "    An entry vector X of size : " << ne.size_X_ << "\n"
        << "    A vector W of weights : ";
    ne.printArr(ne.W_);
    os    << "    A vector dW of weight's derivatives : ";
    ne.printArr(ne.dW_);
    os << "    A biais b : " << ne.biais_ << "\n"
        << "    An activation function named : " << ne.activation_fct_name_ << "\n"
        << "    A post activation value po of : " << ne.po_ << "\n";

    return os;
}










