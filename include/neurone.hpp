#ifndef NEURONE_HPP
#define NEURONE_HPP


class neurone {
    public:
    // default constructor
    neurone () {
        m_size = 0, m_po = 0.; m_biais = 0.; m_db = 0.;
        pfSigma = nullptr, pfDsigma = nullptr, m_W = nullptr, m_dW = nullptr;
    }
    // construtor taking size of an entry vector 
    neurone (int n);
    // copy constructor
    neurone (const neurone & ne);
    // destructor
    ~neurone ();

    // getter setter
    int getSize () const;
    double getBiais () const;
    double getDb () const;
    double getW (int i) const;
    double getDW (int i)const;
    double getPo () const;
    void setBiais (double b);
    void setDb (double db);
    void setW (double w, int i);
    void setDW (double dw, int i);
    void setSigma (double (*pfS)(double));
    void setDsigma (double (*pfDs)(double));

    // operator
    neurone operator= (const neurone & ne);
    bool operator== (const neurone & ne) const;
    bool operator!= (const neurone & ne) const;

    // methods
    void setWones ();
    void setWrandom (); // Unif([-1m, 1m]) distribution
    void setDWzeros ();
    void evaluation (const double *X);

    // tests
    static int unitTest1 (); // tests constuctors 
    static int unitTest2 (); // tests getters setters 
    static int unitTest3 (); // tests operators and methods 

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