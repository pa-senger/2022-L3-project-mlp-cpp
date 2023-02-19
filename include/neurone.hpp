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
    neurone (int n);
    // copy constructor
    neurone (const neurone & ne);
    // destructor
    ~neurone();

    // getter setter
    int getSize () const;
    double getW (int i) const;
    double getDw (int i)const;
    double getPo () const;
    void setW (double w, int i);
    void setDw (double dw, int i);
    void setSigma (double (*pfS)(double d));
    void setDsigma (double (*pfDs)(double d));

    // operator
    neurone operator= (const neurone & ne);

    // methods
    void WOnes ();
    void WRandom (); // todo
    void dWZeros ();
    void evaluation (const double *X);
    int getSize (const double * arr) const; // return the size of any 1D array

    

    private:
    int m_size;
    double (*pfSigma)(double d);
    double (*pfDsigma)(double d);
    double *m_W;
    double *m_dW;
    double m_po;


};



#endif