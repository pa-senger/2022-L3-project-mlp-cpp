#ifndef NEURONE_HPP
#define NEURONE_HPP

class neurone {
    public:
    // default constructor
    neurone () {
        m_size = 0, m_po = 0;
        pfSigma = nullptr, pfDsigma = nullptr, m_W = nullptr, m_dW = nullptr;
    }
    // construtor taking size of entry vector 
    neurone (int n) {
    m_size = n;
    m_po = 0;
    // todo
    }
    // copy constructor
    neurone (const neurone & ne);
    // destructor
    ~neurone();
    

    private:
    int m_size;
    double (*pfSigma)(double * tab);
    double (*pfDsigma)(double * tab);
    double **m_W;
    double **m_dW;
    double m_po;


};



#endif