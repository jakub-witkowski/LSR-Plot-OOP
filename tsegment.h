#ifndef TSEGMENT_H
#define TSEGMENT_H

class TData;

/* include ROOT classes */
#include "TF1.h" // ROOT class for defining 1-dimensional functions
#include "TGraph.h" // ROOT class enabling the creation of plots with X and Y axes and a set of points
#include "TCanvas.h" // ROOT graphics class
// #include "TMultiGraph.h" // A TMultiGraph allows to manipulate a set of graphs as a single entity (from ROOT documentation)

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

    void plot_to_png(std::string);

    /* setter functions */
    void set_ages(double);
    void set_depths(double);
    // void set_g1_ptr();
    
    /* getter functions */
    TData* get_dataset_ptr();
    size_t get_index_from();
    size_t get_index_to();
    double get_ages(int);
    double get_depths(int);
    size_t get_ages_vector_size();
    size_t get_depths_vector_size();

private:
    TData* dset{nullptr}; // set by the constructor at initialisation
    size_t index_from{};
    size_t index_to{};

    std::vector<double> ages{};
    std::vector<double> depths{};

    TF1* f1 {nullptr}; //= new TF1("f1", "pol 4");
    TCanvas* cnv = new TCanvas();
    TGraph* g1 = new TGraph(this->ages.size(), &this->ages[0], &this->depths[0]);
    TGraph* g2{nullptr}; //= new TGraph();

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
