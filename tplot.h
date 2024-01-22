#ifndef TPLOT_H
#define TPLOT_H

class TSegment;

/* include ROOT classes */
#include "TGraph.h" // ROOT class enabling the creation of plots with X and Y axes and a set of points
#include "TCanvas.h" // ROOT graphics class
#include "TMultiGraph.h" // A TMultiGraph allows to manipulate a set of graphs as a single entity (from ROOT documentation)
#include "TAxis.h"

#include <vector>

class TPlot
{
    public:
    TPlot();
    ~TPlot();

    private:
    std::vector<double> depths{};
    std::vector<double> ages{};
    std::vector<double> lsr_plot_values{};
    std::vector<double> smoothed_lsr_plot_values{};
    std::vector<double> lsr_plot_ages{};

    TCanvas* cnv = new TCanvas();
    TMultiGraph* multi1 = new TMultiGraph();
    TMultiGraph* multi2 = new TMultiGraph();
    TGraph* g1{nullptr};
    TGraph* g2{nullptr};
    TGraph* g3{nullptr};
    TGraph* g4{nullptr};
};

#endif