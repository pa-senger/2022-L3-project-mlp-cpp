#include "../include/neurone.hpp"
#include <iostream>
#include <cmath>

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
double neurone:: getDw (int i) const { return m_dW[i] ; }
double neurone:: getPo () const { return m_po; }
void neurone:: setBiais (double d) { m_biais = d; }
void neurone:: setDb (double db) { m_db = db; }
void neurone:: setW (double w, int i) { m_W[i] = w; }
void neurone:: setDw (double dw, int i) { m_dW[i] = dw; }
void neurone:: setSigma (double (*pfS)(double d)) { pfSigma = pfS; }
void neurone:: setDsigma (double (*pfDs)(double d)) { pfDsigma = pfDs; }
neurone neurone:: operator= (const neurone & ne) {
    if ( this != &ne ) {
        m_size = ne.m_size;
        m_po = ne.m_po;
        m_biais = ne.m_biais;
        m_db = ne.m_db;
        pfSigma = ne.pfSigma;
        pfDsigma = ne.pfDsigma;
        if (m_W != nullptr) {
            delete m_W;
           // double * m_W;
        }
        if (m_dW != nullptr) {
            delete m_dW;
           // double * m_W;
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
void neurone:: WOnes () {
    if ( m_W != nullptr ) {
       delete [] m_W;
       //double * m_W;
    }
    m_W = new double [m_size];   
    for (int i=0; i<m_size; ++i) {
        m_W[i] = 1.;
    }
}
void neurone:: dWZeros () {
    if ( m_dW != nullptr ) {
       delete [] m_dW;
      // double * m_dW;
    }
    m_dW = new double [m_size];   
    for (int i=0; i<m_size; ++i) {
        m_dW[i] = 0.;
    }
}
void neurone:: evaluation (const double *X) {
    double dot = 0;
    if ( m_size != getSize(X) ) {
        std::cout << "Error : W and X are not the same dimensions ! \n";
        exit(1);
    }
    for (int i=0; i<m_size; ++i) {
        dot += m_W[i] * X[i];
    }
    m_po = pfSigma(dot + m_biais);
}
int neurone:: getSize (const double * arr) const {
    int size = sizeof(arr)/sizeof(double);
    return size;
}


// ! Unit Tests

double sigma (double x) {
    double res;
    res = (1. / (1+exp(-x)));
    return res;
}

bool neurone:: unitTest1 () { // tests constuctor 
    bool all_passed = false;
    int passed = 0, total = 5;

    neurone n;
    neurone n1(5);
    neurone n2(n1);

    if (n.m_size == 0. && n.m_po == 0. && n.m_biais == 0. && n.m_db == 0. &&
    n.pfSigma == nullptr && n.pfDsigma == nullptr && n.m_W == nullptr && n.m_dW == nullptr)
        ++passed;
    int k = 0;
    for (int i=0; i<n.m_size; ++i) {
        if (n.m_W[i] == 0. && n.m_dW[i] == 0.)   
            ++k;
    }
    if (k % n.m_size == 0)
        ++passed;

    if (n1.m_size == 5 && n1.m_po == 0. && n1.m_biais == 0. && n1.m_db == 0. &&
    n1.pfSigma == nullptr && n1.pfDsigma == nullptr && n1.m_W == nullptr && n1.m_dW == nullptr)
        ++passed;
    k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n1.m_W[i] == 0. && n1.m_dW[i] == 0.)   
            ++k;
    }
    if (k % n1.m_size == 0)
        ++passed;

    if (n2.m_size == n1.m_size && n2.m_po == n1.m_po && n2.m_biais == n1.m_biais &&
    n2.m_db == n1.m_db && n2.pfSigma == n1.pfSigma && n2.pfDsigma == n1.pfDsigma )
        ++passed;
    k = 0;
    for (int i=0; i<n1.m_size; ++i) {
        if (n2.m_W[i] == n1.m_W[i] && n2.m_dW[i] == n1.m_dW[i])   
            ++k;
    }
    if (k % n2.m_size == 0)
        ++passed;

    if (passed % total == 0)    
        all_passed = true;
    return all_passed;
}







