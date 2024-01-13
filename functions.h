#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "tdata.h"

/* scans the depths vector for repeated values
and returns the number of repettions, treating them as hiatuses */
int find_hiatus(TData* d)
{
    int number_of_hiatuses{};

    for (int i = 1; i < d->depths.size(); i++)
    {
        if (d->depths[i] == d->depths[i-1])
            number_of_hiatuses++;
    }

    return number_of_hiatuses;
}

#endif // FUNCTIONS_H