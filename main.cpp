#include "tdata.h"
//#include "tplot.h"
#include "functions.h"
#include <iostream>
//#include "tsegment.h"

int number_of_segments{};

int main(int argc, char** argv)
{
    if (!argv[1])
    {
        std::cout << "No filename given!" << std::endl;
        exit(EXIT_FAILURE);
    }

    TData * dataset = new TData(argv[1]);

    dataset->load_input();
    dataset->display_raw_data();
    dataset->display_ages_vector();
    dataset->display_depths_vector();

    /* Test if data is sorted */
    if (!is_data_sorted(dataset, 'd'))
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!is_data_sorted(dataset, 'a'))
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    dataset->~TData();

    return 0;
}
