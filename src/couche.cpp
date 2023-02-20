#include "../include/couche.hpp"
#include "../include/neurone.hpp"


couche:: couche (const couche & co) {
    m_nbNeurones = co.m_nbNeurones;
    m_nbData = co.m_nbData;
    m_arrNeurones = new neurone[m_nbNeurones];
    for (int i=0; i<m_nbNeurones; ++i)
        m_arrNeurones[i] = co.m_arrNeurones[i];
}
couche:: couche (int nbData, int nbNe) {
    m_nbNeurones = nbNe;
    m_nbData = nbData;
    m_arrNeurones = new neurone[nbNe];
    for (int i=0; i<nbNe; ++i)
        m_arrNeurones[i] = neurone(nbData);
}
couche:: ~couche() {
    if (m_arrNeurones != nullptr)
        delete [] m_arrNeurones;
}

