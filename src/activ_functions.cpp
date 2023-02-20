#include "../include/activ_functions.hpp"
#include <cmath>


double sigma (double x) {
    double res;
    res = (1. / (1 + exp(-x)));
    return res;
}
double dSigma (double x) {
    double res;
    res = (double) exp(-x) / (1 + exp(-x) * (1 + exp(-x)));
    return res;
}