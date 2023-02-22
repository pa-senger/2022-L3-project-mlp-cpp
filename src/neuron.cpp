#include "../include/neuron.hpp"
#include <iostream>
#include <cmath>
#include <random>


neuron:: neuron (unsigned int n) {
    size_X_ = n;
    post_activation_value_ = 0.;
    biais_ = 0.;
    db_ = 0.;
    pf_activation_ = &ReLU;
    pf_activation_d_ = &dReLU;
    activation_fct_name_ = "ReLU";
    if (n == 0 ) {
        Weight_ = nullptr;
        dWeight_ = nullptr;
    }
    else {
        Weight_ = new double [n];
        dWeight_ = new double [n];
        for (unsigned int i=0; i<n; ++i) {
            Weight_[i] = 1.;
            dWeight_[i] = 0.;
        }
    }
}
neuron:: neuron (const neuron &ne) {
    size_X_ = ne.size_X_;
    post_activation_value_ = ne.post_activation_value_;
    biais_ = ne.biais_;
    db_ = ne.db_;
    pf_activation_ = ne.pf_activation_; // pointer to the same "object"
    pf_activation_d_ = ne.pf_activation_d_; // functions arent object so they cant be deep copied
    activation_fct_name_ = ne.activation_fct_name_;
    if (size_X_ == 0) {
        Weight_ = nullptr;
        dWeight_ = nullptr;
    }
    else {
        Weight_ = new double [size_X_];
        dWeight_ = new double [size_X_];
        for (unsigned int i=0; i<size_X_; ++i) {
            Weight_[i] = ne.Weight_[i];
            dWeight_[i] = ne.dWeight_[i];
        }
    }
} 
neuron:: ~neuron () { 
    if ( Weight_ != nullptr)
        delete [] Weight_;
    if ( dWeight_ != nullptr)
        delete [] dWeight_;    
}
int neuron:: getSizeX () const { return size_X_; }
double neuron:: getBiais () const { return biais_; }
double neuron:: getDb () const { return db_; }
double neuron:: getWeight (unsigned int i) const {
    double weight = 0;
    if (i < size_X_  && Weight_ != nullptr)
        weight = Weight_[i]; 
    return weight;
}
double neuron:: getDWeight (unsigned int i) const {
    double dw = 0;
    if (i < size_X_ && Weight_ != nullptr)
        dw = dWeight_[i]; 
    return dw;
}
double neuron:: getPo () const { return post_activation_value_; }
void neuron:: setBiais (double b) { biais_ = b; }
void neuron:: setDb (double db) { db_ = db; }
void neuron:: setWeight (double Weight, unsigned int i) {
    if (i < size_X_ && Weight_ != nullptr)
        Weight_[i] = Weight; 
}
void neuron:: setDWeight (double dWeight, unsigned int i) {
    if (i < size_X_ && Weight_ != nullptr)
        dWeight_[i] = dWeight; 
}
void neuron:: setActivationFcts (double (*pf_a)(double), double (*pf_da)(double), std::string name) {
    pf_activation_ = pf_a;
    pf_activation_d_ = pf_da;
    activation_fct_name_ = name;
}
neuron neuron:: operator= (const neuron &ne) {
    if ( this != &ne ) {
        size_X_ = ne.size_X_;
        post_activation_value_ = ne.post_activation_value_;
        biais_ = ne.biais_;
        db_ = ne.db_;
        pf_activation_ = ne.pf_activation_;
        pf_activation_d_ = ne.pf_activation_d_;
        if (Weight_ != nullptr) {
            delete [] Weight_;
        }
        if (dWeight_ != nullptr) {
            delete [] dWeight_;
        }
        if (size_X_ == 0) {
            Weight_ = nullptr;
            dWeight_ = nullptr;
        }
        else {
            Weight_ = new double [size_X_];
            dWeight_ = new double [size_X_];
            for (unsigned int i=0; i<size_X_; ++i) {
                Weight_[i] = ne.Weight_[i];
                dWeight_[i] = ne.dWeight_[i];
            }
        }   
    }
    return *this;
}
void neuron:: setWeightsOnes () {
    if (Weight_ != nullptr) {
       delete [] Weight_;
    }
    if (size_X_ == 0) {
        Weight_ = nullptr;
    }
    else {
        Weight_ = new double [size_X_];   
        for (unsigned int i=0; i<size_X_; ++i) {
            Weight_[i] = 1;
    }
    }
}
void neuron:: setDWeightsZeros () {
    if (dWeight_ != nullptr) {
       delete [] dWeight_;
    }
    if (size_X_ == 0) {
        Weight_ = nullptr;
    }
    else {
        dWeight_ = new double [size_X_];   
        for (unsigned int i=0; i<size_X_; ++i) {
            dWeight_[i] = 0;
        }
    }
}
void neuron:: setWeightsRandom () {
    std::random_device rd;
    std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(-1'000'000, 1'000'000);
    if (Weight_ != nullptr)
        delete [] Weight_;
    if (size_X_ == 0) {
        Weight_ = nullptr;
    }
    else {
        Weight_ = new double[size_X_];
        for (unsigned int i=0; i<size_X_; ++i) 
            Weight_[i] = dis(gen);
    }
}
void neuron:: activate (const double *X, unsigned int size) {
    if (size == size_X_) {
        double dot = 0;
        for (unsigned int i=0; i<size_X_; ++i) {
            dot += (Weight_[i] * X[i]);
    }
        post_activation_value_ = pf_activation_(dot + biais_);
    }
}
bool neuron:: operator== (const neuron &ne) const {
    bool res = true;
    if(size_X_ != ne.size_X_ || pf_activation_ != ne.pf_activation_ || pf_activation_d_ != ne.pf_activation_d_ ||
        post_activation_value_ != ne.post_activation_value_ || biais_ != ne.biais_ || db_ != ne.db_)
        return false;
    for (unsigned int i=0; i<size_X_; ++i) {
        if (Weight_[i] != ne.Weight_[i] || dWeight_[i] != ne.dWeight_[i])
        return false;
    }
    return res;
}
bool neuron:: operator!= (const neuron &ne) const {
    return !(*this == ne);
}
void neuron:: printWeights (const double *arr) const {
    if ( arr != nullptr) {
        std::cout << "[";
        for (unsigned int i=0; i<size_X_-1; ++i) {
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
        << "    A vector of weights : ";
    ne.printWeights(ne.Weight_);
    os    << "    A vector of weight's derivatives : ";
    ne.printWeights(ne.dWeight_);
    os << "    A biais b : " << ne.biais_ << "\n"
        << "    An activation function named : " << ne.activation_fct_name_ << "\n"
        << "    A post activation value of : " << ne.post_activation_value_ << "\n";

    return os;
}
double neuron:: evaluateFct (double x) const {
    double res = 0;
    if (pf_activation_ != nullptr)
        res = pf_activation_(x);
    return res;
}
double neuron:: evaluateFctDerivative (double x) const {
    double res = 0;
    if (pf_activation_d_ != nullptr)
        res = pf_activation_d_(x);
    return res;
}









