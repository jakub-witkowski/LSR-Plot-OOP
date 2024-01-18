#include "tsegment.h"
#include "tdata.h"
#include <iostream>

TSegment::TSegment(TData* ds, size_t f, size_t t) : dset(ds), index_from(f), index_to(t)
{
    std::cout << "TSegment Constructor" << std::endl;
}

TSegment::~TSegment()
{
    std::cout << " TSegment ~Destructor" << std::endl;
}

void TSegment::display_ages_vector()
{
    std::cout << "Data in the ages vector: " << std::endl;
    for (int i = 0; i < get_ages_vector_size(); i++)
    {
        std::cout << i << ": " << get_ages(i) << std::endl;
    }
}

void TSegment::display_depths_vector()
{
    std::cout << "Data in the depths vector: " << std::endl;
    for (int i = 0; i < get_depths_vector_size(); i++)
    {
        std::cout << i << ": " << get_depths(i) << std::endl;
    }
}

void TSegment::display_lsr_values_vector()
{
    std::cout << "Data in the lsr_values vector: " << std::endl;
    for (int i = 0; i < get_lsr_values_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_values[i] << std::endl;
    }
}

void TSegment::display_lsr_plot_values_vector()
{
    std::cout << "Data in the lsr_plot_values vector: " << std::endl;
    for (int i = 0; i < get_lsr_plot_values_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_plot_values[i] << std::endl;
    }
}

void TSegment::display_lsr_plot_ages_vector()
{
    std::cout << "Data in the lsr_plot_ages vector: " << std::endl;
    for (int i = 0; i < get_lsr_plot_ages_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_plot_ages[i] << std::endl;
    }
}

void TSegment::compute_lsr_values()
{
    for (int i = 1; i < this->ages.size(); i++)
    {
        this->lsr_values.push_back(((this->depths[i] - this->depths[i-1]) * 100) / ((this->ages[i] - this->ages[i-1]) * 1000));
    }

    for (int i = 0; i < this->ages.size() - 1; i++)
    {
        this->lsr_plot_values.push_back(this->lsr_values[i]);
        this->lsr_plot_values.push_back(this->lsr_values[i]);
        this->lsr_plot_ages.push_back(this->ages[i]);
        this->lsr_plot_ages.push_back(this->ages[i+1]);
    }
}

void TSegment::compute_polynomial_expression()
{}

void TSegment::copy_ages_to_segment()
{
    for (int i = this->index_from; i < this->index_to; i ++)
    {
        this->set_ages(this->dset->get_ages(i));
    }
}

void TSegment::copy_depths_to_segment()
{
    for (int i = this->index_from; i < this->index_to; i ++)
    {
        this->set_depths(this->dset->get_depths(i));
    }
}

void TSegment::plot_to_png(std::string f)
{
    this->cnv->Divide(2,1);
    this->cnv->cd(1);
    this->g1->SetTitle("Age vs Depth, raw");
    this->g1->SetMarkerColor(4);
    this->g1->SetMarkerSize(1.25);
    this->g1->SetMarkerStyle(20);
    this->g1->Draw("A RY P");
    
    this->cnv->cd(2);
    this->g2->SetTitle("LSR variability, raw");
    this->g2->SetLineColor(4);
    this->g2->SetLineWidth(2);
    this->g2->Draw("AL");

    this->cnv->Print(f.c_str());
}

/* setter functions */
void TSegment::set_ages(double a)
{
    this->ages.push_back(a);
}

void TSegment::set_depths(double d)
{
    this->depths.push_back(d);
}

void TSegment::set_g1_ptr()
{
    this->g1 = new TGraph(this->ages.size(), &this->ages[0], &this->depths[0]);
}

void TSegment::set_g2_ptr()
{
    this->g2 = new TGraph(this->lsr_plot_ages.size(), &this->lsr_plot_ages[0], &this->lsr_plot_values[0]);
}

/* getter functions */
TData* TSegment::get_dataset_ptr()
{
    return this->dset;
}

size_t TSegment::get_index_from()
{
    return this->index_from;
}

size_t TSegment::get_index_to()
{
    return this->index_to;
}

double TSegment::get_ages(int i)
{
    return this->ages[i];
}

double TSegment::get_depths(int i)
{
    return this->depths[i];
}

size_t TSegment::get_ages_vector_size()
{
    return this->ages.size();
}

size_t TSegment::get_depths_vector_size()
{
    return this->depths.size();
}

size_t TSegment::get_lsr_values_vector_size()
{
    return this->lsr_values.size();
}

size_t TSegment::get_lsr_plot_values_vector_size()
{
    return this->lsr_plot_values.size();
}

size_t TSegment::get_lsr_plot_ages_vector_size()
{
    return this->lsr_plot_ages.size();
}