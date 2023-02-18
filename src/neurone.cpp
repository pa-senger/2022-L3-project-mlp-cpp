#include "../include/neurone.hpp"


neurone:: neurone (const neurone & ne) {
    m_size = ne.m_size;
    m_po = ne.m_po;
    pfSigma = ne.pfSigma; // pointer to the same "object"
    pfDsigma = ne.pfDsigma; // functions arent object so they cant be deep copied
    m_W = new double * [2]; // 2D arrray
    m_W[0] = new double[m_size]; // vecteur W
    m_W[1] = new double[1]; // biais b
    m_dW = new double * [2];
    m_dW[0] = new double[m_size]; // vecteur dW
    m_dW[1] = new double[1]; // db
    for (int j=0; j<m_size; ++j) {
        m_W[0][j] = ne.m_W[0][j]; // copy of W
        m_dW[0][j] = ne.m_dW[0][j]; // copy of dW 
    }
    m_W[1] = ne.m_W[1]; // copy of b
    m_dW[1] = ne.m_dW[1]; // copy of db
}
neurone:: ~neurone () { 
    for (int i=0; i<2; i++) {
        delete [] m_W[i];
        delete [] m_dW[i];
        }
    }