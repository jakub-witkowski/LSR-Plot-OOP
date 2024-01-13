#ifndef TSEGMENT_H
#define TSEGMENT_H

/* include ROOT classes */
#include "TF1.h"

/* #include "TGraph.h"
#include "TMultiGraph.h"*/

#include <vector>

class TSegment
{
public:
    TSegment();
    ~TSegment();

    void compute_lsr_values();
    void compute_polynomial_expression();

    /* getter functions */
    double get_age(int);
    double get_depth(int);

private:
    TF1 f1;

    std::vector<double> ages{};
    std::vector<double> depths{};

    std::vector<double> lsr_values{};
    std::vector<double> lsr_values_plot{};
    std::vector<double> lsr_values_ages{};
    std::vector<double> smoothed_lsr_values{};
    std::vector<double> smoothed_lsr_values_plot{};

    double par[10]{};
    double chi2{};
    int ndf{};
};

#endif // TSEGMENT_H
