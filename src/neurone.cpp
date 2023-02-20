#include "../include/neurone.hpp"
#include <iostream>
#include <cmath>
#include <random>


neurone:: neurone (int n) {
    m_size = n;
    m_po = 0.;
    m_biais = 0.;
    m_db = 0.;
    pfSigma = nullptr;
    pfDsigma = nullptr;
    m_W = new double [n];
    m_dW = new double [n];
    for (int i=0; i<n; ++i) {
        m_W[i] = 0.;
        m_dW[i] = 0.;
    }
}
neurone:: neurone (const neurone & ne) {
    m_size = ne.m_size;
    m_po = ne.m_po;
    m_biais = ne.m_biais;
    m_db = ne.m_db;
    pfSigma = ne.pfSigma; // pointer to the same "object"
    pfDsigma = ne.pfDsigma; // functions arent object so they cant be deep copied
    m_W = new double [m_size];
    m_dW = new double [m_size];
    for (int i=0; i<m_size; ++i) {
        m_W[i] = ne.m_W[i];
        m_dW[i] = ne.m_dW[i];
    }
} 
neurone:: ~neurone () { 
    delete [] m_W;
    delete [] m_dW;    
}
int neurone:: getSize () const { return m_size; }
double neurone:: getBiais () const { return m_biais; }
double neurone:: getDb () const { return m_db; }
double neurone:: getW (int i) const { return m_W[i]; }
double neurone:: getDW (int i) const { return m_dW[i] ; }
double neurone:: getPo () const { return m_po; }
void neurone:: setBiais (double b) { m_biais = b; }
void neurone:: setDb (double db) { m_db = db; }
void neurone:: setW (double w, int i) { m_W[i] = w; }
void neurone:: setDW (double dw, int i) { m_dW[i] = dw; }
void neurone:: setSigma (double (*pfS)(double)) { pfSigma = pfS; }
void neurone:: setDsigma (double (*pfDs)(double)) { pfDsigma = pfDs; }
neurone neurone:: operator= (const neurone & ne) {
    if ( this != &ne ) {
        m_size = ne.m_size;
        m_po = ne.m_po;
        m_biais = ne.m_biais;
        m_db = ne.m_db;
        pfSigma = ne.pfSigma;
        pfDsigma = ne.pfDsigma;
        if (m_W != nullptr) {
            delete [] m_W;
        }
        if (m_dW != nullptr) {
            delete [] m_dW;
        }
        m_W = new double [m_size];
        m_dW = new double [m_size];
        for (int i=0; i<m_size; ++i) {
            m_W[i] = ne.m_W[i];
            m_dW[i] = ne.m_dW[i];
        }   
    }
    return *this;
}
void neurone:: setWones () {
    if ( m_W != nullptr ) {
       delete [] m_W;
    }
    m_W = new double [m_size];   
    for (int i=0; i<m_size; ++i) {
        m_W[i] = 1.;
    }
}
void neurone:: setDWzeros () {
    if ( m_dW != nullptr ) {
       delete [] m_dW;
    }
    m_dW = new double [m_size];   
    for (int i=0; i<m_size; ++i) {
        m_dW[i] = 0.;
    }
}
void neurone:: setWrandom () {
    std::random_device rd;
    std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(-1'000'000, 1'000'000);
    for (int i=0; i<m_size; ++i) 
        m_W[i] = dis(gen);
}
void neurone:: evaluation (const double *X) {
    double dot = 0;
    if ( m_size != getSizeArr(X) ) {
        std::cout << "Error : W and X are not the same dimensions ! \n";
        exit(1);
    }
    for (int i=0; i<m_size; ++i) {
        dot += m_W[i] * X[i];
    }
    m_po = pfSigma(dot + m_biais);
}
int neurone:: getSizeArr (const double * arr) const {
    int size = sizeof(arr)/sizeof(double);
    return size;
}








