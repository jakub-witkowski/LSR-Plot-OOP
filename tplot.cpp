#include "tplot.h"
#include "tsegment.h"

#include <iostream>
#include <vector>

TPlot::TPlot()
{
    std::cout << "TPlot Constructor" << std::endl;
}

TPlot::~TPlot()
{
    std::cout << " TPlot ~Destructor" << std::endl;
}

void TPlot::copy_ages_to_plot()
{
    for (int i = 0; i < this->segm_ptr->get_ages_vector_size(); i++)
    {
        this->set_ages(this->segm_ptr->get_ages(i));
    }
}

void TPlot::copy_depths_to_plot()
{
    for (int i = 0; i < this->segm_ptr->get_depths_vector_size(); i++)
    {
        this->set_depths(this->segm_ptr->get_depths(i));
    }
}

void TPlot::copy_fit_line_to_plot()
{
    for (int i = 0; i < this->segm_ptr->get_fit_line_vector_size(); i++)
    {
        this->set_fit_line(this->segm_ptr->get_fit_line(i));
    }
}

void TPlot::copy_lsr_plot_values_to_plot()
{
    for (int i = 0; i < this->segm_ptr->get_lsr_plot_values_vector_size(); i++)
    {
        this->set_lsr_plot_values(this->segm_ptr->get_lsr_plot_value(i));
    }
}

void TPlot::copy_smoothed_lsr_plot_values_to_plot()
{

}

void TPlot::copy_lsr_plot_ages_to_plot()
{
    
}

/* displays data stored in the ages vector of a TSegment object */
void TPlot::display_ages_vector()
{
    std::cout << "Data in the ages vector: " << std::endl;
    for (int i = 0; i < get_ages_vector_size(); i++)
    {
        std::cout << i << ": " << this->ages[i] << std::endl;
    }
}

void TPlot::plot_to_png()
{

}

void TPlot::set_ages(double a)
{
    this->ages.push_back(a);
}

void TPlot::set_depths(double d)
{
    this->depths.push_back(d);
}

void TPlot::set_fit_line(double d)
{
    this->fit_line.push_back(d);
}

void TPlot::set_lsr_plot_values(double d)
{

}

void TPlot::set_smoothed_lsr_plot_values(double d)
{

}

void TPlot::set_lsr_plot_ages(double d)
{

}

void TPlot::set_segm_ptr(TSegment* s)
{
    this->segm_ptr = s;
}

void TPlot::set_g1_ptr()
{
    this->g1 = new TGraph(this->ages.size(), &this->ages[0], &this->depths[0]);
}

void TPlot::set_g2_ptr()
{
    this->g2 = new TGraph(this->ages.size(), &this->ages[0], &this->fit_line[0]);
}

void TPlot::set_g3_ptr()
{
    this->g3 = new TGraph(this->lsr_plot_ages.size(), &this->lsr_plot_ages[0], &this->lsr_plot_values[0]);
}

void TPlot::set_g4_ptr()
{
    this->g4 = new TGraph(this->lsr_plot_ages.size(), &this->lsr_plot_ages[0], &this->smoothed_lsr_plot_values[0]);
}

/* getter functions */
size_t TPlot::get_ages_vector_size()
{
    return this->ages.size();
}