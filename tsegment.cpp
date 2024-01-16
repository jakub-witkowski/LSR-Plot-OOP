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

void TSegment::compute_lsr_values()
{}

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
    this->g1->SetMarkerColor(4);
    this->g1->SetMarkerSize(1.25);
    this->g1->Draw("A RY P");
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