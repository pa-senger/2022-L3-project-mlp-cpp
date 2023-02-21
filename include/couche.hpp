#ifndef COUCHE_HPP
#define COUCHE_HPP
#include "../include/neurone.hpp"


class couche {
  public:
    couche () : nb_neurones_(0), nb_data_(0), arr_neurones_(nullptr) {}
    couche (const couche & co);
    couche (int nb_data, int nb_ne);
    ~couche ();

    double getW (int i, int j) const; // i-th neurone, j-th weight
    double getDW (int i, int j) const; // i-th neurone, j-th derivative of W
    int getNbData () const;
    double getNbNeurones () const;
    double getPo (int i) const; // get po of the i-th neurone
    void setW (double val, int i, int j);
    void setDW (double val, int i, int j);



    static int unitTest1(); // tests constructors
    static int unitTest2(); // tests getters setters

  private:
    int nb_neurones_;
    int nb_data_;
    neurone * arr_neurones_;
};




#endif