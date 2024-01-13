#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "tdata.h"

void display_member_vector_dbl(TData* d, char c)
{
    switch(c)
    {
        case 'a':
        for (auto it : d->ages)
            std::cout << it << std::endl;
        break;
        case 'd':
        for (auto it : d->depths)
            std::cout << it << std::endl;
        break;
    }
}

/* tests if a vector is sorted */
bool is_data_sorted(TData* d, char c)
{
    bool result{true};

    if (c == 'a')
    {
        for (int i = 1; i < d->ages.size(); i++)
        {
            if (d->ages[i] < d->ages[i-1])
                result = false;
        }
    }
    else if (c == 'd')
    {
        for (int i = 1; i < d->depths.size(); i++)
        {
            if (d->depths[i] < d->depths[i-1])
                result = false;
        }
    }

    return result;
}

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