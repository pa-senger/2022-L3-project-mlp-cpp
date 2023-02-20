#ifndef COUCHE_HPP
#define COUCHE_HPP
#include "../include/neurone.hpp"


class couche {
    public:
    couche () : m_nbNeurones(0), m_nbData(0), m_arrNeurones(nullptr) {}
    couche (const couche & co);
    couche (int nbData, int nbNe);
    ~couche ();


    static bool unitTest1(); // tests constructors

    private:
    int m_nbNeurones;
    int m_nbData;
    neurone * m_arrNeurones;
};




#endif