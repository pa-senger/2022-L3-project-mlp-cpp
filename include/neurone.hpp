#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <iostream>
#include <string>


class neurone {
  public:
    // default constructor
    neurone () {
        size_X_ = 0, po_ = 0.; biais_ = 0.; db_ = 0.;
        pf_sigma_ = nullptr, pf_d_sigma_ = nullptr, W_ = nullptr, dW_ = nullptr;
    }
    // construtor taking size of an entry vector 
    neurone (int n);
    // copy constructor
    neurone (const neurone & ne);
    // destructor
    ~neurone ();

    // getter setter
    int getSizeX () const;
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
    void setActivFctName (std::string sigma);

    // operator
    neurone operator= (const neurone & ne);                                     
    bool operator== (const neurone & ne) const;
    bool operator!= (const neurone & ne) const;
    friend std::ostream& operator<< (std::ostream& os, const neurone& ne);

    // methods
    void setWones ();
    void setWrandom (); // Unif([-1m, 1m]) distribution
    void setDWzeros ();
    void evaluation (const double *X);
    void printArr (const double *arr) const;

    // tests
    static int unitTest1 (); // tests constuctors 
    static int unitTest2 (); // tests getters setters 
    static int unitTest3 (); // tests operators and methods 

  private:
    int size_X_;
    double (*pf_sigma_) (double);
    double (*pf_d_sigma_) (double);
    double *W_;
    double *dW_;
    double po_;
    double biais_;
    double db_;
    std::string activ_fct_name_;
};


#endif