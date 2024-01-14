#include "tsegment.h"
//#include "tdata.h"
#include <iostream>

TSegment::TSegment(size_t f, size_t t) : index_from(f), index_to(t)
{
    
    std::cout << "TSegment Constructor" << std::endl;
}

TSegment::~TSegment()
{
    std::cout << "TSegment Destructor" << std::endl;
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
        ;
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
double TSegment::get_age(int i)
{
    return this->ages[i];
}

double TSegment::get_depth(int i)
{
    return this->depths[i];
}