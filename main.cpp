#include "tdata.h"
#include "tsegment.h"
// #include "functions.h"
#include <iostream>

int number_of_segments{};
std::vector<TSegment*> segments{}; 

int main(int argc, char** argv)
{
    if (!argv[1])
    {
        std::cout << "No filename given!" << std::endl;
        exit(EXIT_FAILURE);
    }

    TData * dataset = new TData(argv[1]);

    dataset->load_input();
    // dataset->display_raw_data();
    // dataset->display_ages_vector();
    // dataset->display_depths_vector();

    /* Test if data is sorted */
    if (!dataset->test_input_order())
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Number of segments: " << dataset->find_hiatus() + 1 << std::endl;

    for (int i = 0; i < number_of_segments; i++)
    {
        segments.push_back(new TSegment());
    }

    dataset->~TData();

    return 0;
}
