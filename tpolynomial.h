#ifndef TPOLYNOMIAL_H
#define TPOLYNOMIAL_H

#include "TF1.h"
#include <string>
#include <vector>

class TPolynomial
{
    public:
    TPolynomial(int);

    int deg{};
    std::string phrase{};
    TF1* f{nullptr};
    std::vector<double> parameters{};
    double chi2{};
    int ndf{};  
};

#endif