#ifndef NEURONE_HPP
#define NEURONE_HPP

class neurone {
    public:
    // default constructor
    neurone () {
        m_size = 0., m_po = 0.; m_biais = 0.; m_db = 0.;
        pfSigma = nullptr, pfDsigma = nullptr, m_W = nullptr, m_dW = nullptr;
    }
    // construtor taking size of an entry vector 
    neurone (int n);
    // copy constructor
    neurone (const neurone & ne);
    // destructor
    ~neurone();

    // getter setter
    int getSize () const;
    double getBiais () const;
    double getDb () const;
    double getW (int i) const;
    double getDw (int i)const;
    double getPo () const;
    void setBiais (double d);
    void setDb (double db);
    void setW (double w, int i);
    void setDw (double dw, int i);
    void setSigma (double (*pfS)(double));
    void setDsigma (double (*pfDs)(double));

    // operator
    neurone operator= (const neurone & ne);

    // methods
    void WOnes ();
    void WRandom (); // todo
    void dWZeros ();
    void evaluation (const double *X);
    int getSize (const double * arr) const; // return the size of any 1D array

    // tests
    static bool unitTest1 (); // tests constuctor 
    static bool unitTest2 (); // tests getters setters
    static bool unitTest3 (); // tests operators and methods

    private:
    int m_size;
    double (*pfSigma) (double);
    double (*pfDsigma) (double);
    double *m_W;
    double *m_dW;
    double m_po;
    double m_biais;
    double m_db;
};



#endif