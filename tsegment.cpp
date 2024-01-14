#include "tsegment.h"
#include <iostream>

TSegment::TSegment()
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

/* getter functions */
double TSegment::get_age(int i)
{
    return this->ages[i];
}

double TSegment::get_depth(int i)
{
    return this->depths[i];
}