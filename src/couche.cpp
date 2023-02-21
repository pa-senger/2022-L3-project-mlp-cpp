#include "../include/couche.hpp"
#include "../include/neurone.hpp"


couche:: couche (const couche & co) {
    nb_neurones_ = co.nb_neurones_;
    nb_data_ = co.nb_data_;
    arr_neurones_ = new neurone[nb_neurones_];
    for (int i=0; i<nb_neurones_; ++i)
        arr_neurones_[i] = co.arr_neurones_[i];
}
couche:: couche (int nb_data, int nb_ne) {
    nb_neurones_ = nb_ne;
    nb_data_ = nb_data;
    arr_neurones_ = new neurone[nb_ne];
    for (int i=0; i<nb_ne; ++i)
        arr_neurones_[i] = neurone(nb_data);
}
couche:: ~couche() {
    if (arr_neurones_ != nullptr)
        delete [] arr_neurones_;
}

