#include "../include/neurone.hpp"
#include <iostream>
#include <cmath>
#include <random>


neurone:: neurone (int n) {
    size_X_ = n;
    po_ = 0.;
    biais_ = 0.;
    db_ = 0.;
    pf_sigma_ = nullptr;
    pf_d_sigma_ = nullptr;
    W_ = new double [n];
    dW_ = new double [n];
    for (int i=0; i<n; ++i) {
        W_[i] = 0.;
        dW_[i] = 0.;
    }
}
neurone:: neurone (const neurone & ne) {
    size_X_ = ne.size_X_;
    po_ = ne.po_;
    biais_ = ne.biais_;
    db_ = ne.db_;
    pf_sigma_ = ne.pf_sigma_; // pointer to the same "object"
    pf_d_sigma_ = ne.pf_d_sigma_; // functions arent object so they cant be deep copied
    W_ = new double [size_X_];
    dW_ = new double [size_X_];
    for (int i=0; i<size_X_; ++i) {
        W_[i] = ne.W_[i];
        dW_[i] = ne.dW_[i];
    }
} 
neurone:: ~neurone () { 
    if ( W_ != nullptr)
        delete [] W_;
    if ( dW_ != nullptr)
        delete [] dW_;    
}
int neurone:: getSizeX () const { return size_X_; }
double neurone:: getBiais () const { return biais_; }
double neurone:: getDb () const { return db_; }
double neurone:: getW (int i) const { return W_[i]; }
double neurone:: getDW (int i) const { return dW_[i] ; }
double neurone:: getPo () const { return po_; }
void neurone:: setBiais (double b) { biais_ = b; }
void neurone:: setDb (double db) { db_ = db; }
void neurone:: setW (double w, int i) { W_[i] = w; }
void neurone:: setDW (double dw, int i) { dW_[i] = dw; }
void neurone:: setSigma (double (*pfS)(double)) { pf_sigma_ = pfS; }
void neurone:: setDsigma (double (*pfDs)(double)) { pf_d_sigma_ = pfDs; }
neurone neurone:: operator= (const neurone & ne) {
    if ( this != &ne ) {
        size_X_ = ne.size_X_;
        po_ = ne.po_;
        biais_ = ne.biais_;
        db_ = ne.db_;
        pf_sigma_ = ne.pf_sigma_;
        pf_d_sigma_ = ne.pf_d_sigma_;
        if (W_ != nullptr) {
            delete [] W_;
        }
        if (dW_ != nullptr) {
            delete [] dW_;
        }
        W_ = new double [size_X_];
        dW_ = new double [size_X_];
        for (int i=0; i<size_X_; ++i) {
            W_[i] = ne.W_[i];
            dW_[i] = ne.dW_[i];
        }   
    }
    return *this;
}
void neurone:: setWones () {
    if ( W_ != nullptr ) {
       delete [] W_;
    }
    W_ = new double [size_X_];   
    for (int i=0; i<size_X_; ++i) {
        W_[i] = 1.;
    }
}
void neurone:: setDWzeros () {
    if ( dW_ != nullptr ) {
       delete [] dW_;
    }
    dW_ = new double [size_X_];   
    for (int i=0; i<size_X_; ++i) {
        dW_[i] = 0.;
    }
}
void neurone:: setWrandom () {
    std::random_device rd;
    std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(-1'000'000, 1'000'000);
    for (int i=0; i<size_X_; ++i) 
        W_[i] = dis(gen);
}
void neurone:: evaluation (const double *X) {
    double dot = 0;
    for (int i=0; i<size_X_; ++i) {
        dot += (W_[i] * X[i]);
    }
    po_ = pf_sigma_(dot + biais_);
}
bool neurone:: operator== (const neurone & ne) const {
    bool res = true;
    if(size_X_ != ne.size_X_ || pf_sigma_ != ne.pf_sigma_ || pf_d_sigma_ != ne.pf_d_sigma_ ||
        po_ != ne.po_ || biais_ != ne.biais_ || db_ != ne.db_)
        return false;
    for (int i=0; i<size_X_; ++i) {
        if (W_[i] != ne.W_[i] || dW_[i] != ne.dW_[i])
        return false;
    }
    return res;
}
bool neurone:: operator!= (const neurone & ne) const {
    return !( *this == ne);
}
void neurone:: printArr (const double *arr) const {
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
void neurone:: setActivFctName (std::string sigma) {
    activ_fct_name_ = sigma;
}

std::ostream& operator<< (std::ostream& os, const neurone& ne) {
    os << "The neuron is define with : \n"
        << "    An entry vector of size : " << ne.size_X_ << "\n"
        << "    Its weights : ";
    ne.printArr(ne.W_);
    os    << "    The derivatives of its weights : ";
    ne.printArr(ne.dW_);
    os << "    Its biais : " << ne.biais_ << "\n"
        << "    Its activation function : " << ne.activ_fct_name_ << "\n"
        << "    Its value post activation : " << ne.po_ << "\n";

    return os;
}










