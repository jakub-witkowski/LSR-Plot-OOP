#ifndef TSEGMENT_H
#define TSEGMENT_H

// #include "tdata.h"

class TData;

/* include ROOT classes */
/* #include "TF1.h"

#include "TGraph.h"
#include "TMultiGraph.h"*/

#include <vector>
#include <stdio.h>

class TSegment
{
public:
    TSegment(TData*, size_t, size_t);
    ~TSegment();

    void display_ages_vector();
    void display_depths_vector();

    void compute_lsr_values();
    void compute_polynomial_expression();

    void copy_ages_to_segment();
    void copy_depths_to_segment();

    /* setter function */
    void set_ages(double);
    void set_depths(double);
    
    /* getter functions */
    TData* get_dataset_ptr();
    size_t get_index_from();
    size_t get_index_to();
    double get_ages(int);
    double get_depths(int);
    size_t get_ages_vector_size();
    size_t get_depths_vector_size();

private:
    // TF1 f1;
    TData* dset{nullptr};
    size_t index_from{};
    size_t index_to{};

    std::vector<double> ages{};
    std::vector<double> depths{};

    /*std::vector<double> lsr_values{};
    std::vector<double> lsr_values_plot{};
    std::vector<double> lsr_values_ages{};
    std::vector<double> smoothed_lsr_values{};
    std::vector<double> smoothed_lsr_values_plot{};

    double par[10]{};
    double chi2{};
    int ndf{};*/
};

#endif // TSEGMENT_H
