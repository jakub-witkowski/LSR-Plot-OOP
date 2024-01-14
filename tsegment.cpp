#include "tsegment.h"
#include "tdata.h"
#include <iostream>

TSegment::TSegment(size_t f, size_t t) : index_from(f), index_to(t)
{
    std::cout << "TSegment Constructor" << std::endl;
}

TSegment::~TSegment()
{
    std::cout << "TSegment Destructor" << std::endl;
}

void TSegment::display_ages_vector()
{
    std::cout << "Data in the ages vector: " << std::endl;
    for (int i = 0; i < get_ages_vector_size(); i++)
    {
        std::cout << get_ages(i) << std::endl;
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

void TSegment::copy_ages_to_segment(TData* d, size_t pos_from, size_t pos_to)
{
    for (int i = pos_from; i < pos_to; i ++)
    {
        this->set_ages(d->get_ages(i));
    }
}

void TSegment::copy_depths_to_segment(TData* d, size_t pos_from, size_t pos_to)
{
    for (int i = pos_from; i < pos_to; i ++)
    {
        this->set_depths(d->get_depths(i));
    }
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

/* getter functions */
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