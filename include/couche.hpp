#ifndef COUCHE_HPP
#define COUCHE_HPP
#include "../include/neurone.hpp"


class couche {
    public:
    couche () : nb_neurones_(0), nb_data_(0), arr_neurones_(nullptr) {}
    couche (const couche & co);
    couche (int nb_data, int nb_ne);
    ~couche ();




    static int unitTest1(); // tests constructors

    private:
    int nb_neurones_;
    int nb_data_;
    neurone * arr_neurones_;
};




#endif