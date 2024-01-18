#ifndef TPOLYNOMIAL_H
#define TPOLYNOMIAL_H

#include "TF1.h"

class TPolynomial
{
    public:
    TF1* f{nullptr};
    double par[10]{};
    double chi2{};
    int ndf{};  
};

#endif