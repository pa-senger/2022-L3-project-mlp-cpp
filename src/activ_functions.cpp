#include "../include/activ_functions.hpp"
#include <cmath>


double sigma (const double x) {
    double res;
    res = (1. / (1 + exp(-x)));
    return res;
}
double dSigma (const double x) {
    double res;
    res = (double) exp(-x) / (1 + exp(-x) * (1 + exp(-x)));
    return res;
}