#include "tdata.h"
#include "tsegment.h"
#include <iostream>
#include <iomanip>

// int number_of_segments{};
std::vector<TSegment> segments{}; 

int main(int argc, char** argv)
{
    if (!argv[1])
    {
        std::cout << "No filename given!" << std::endl;
        exit(EXIT_FAILURE);
    }

    TData * dataset = new TData(argv[1]);

    /* Test if data is sorted */
    if (!dataset->test_input_order())
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    dataset->load_input();
    dataset->find_hiatus();

    // dataset->display_raw_data();
    // dataset->display_ages_vector();
    // dataset->display_depths_vector();
    // dataset->display_segment_indexes_vector();

    // std::cout << "Number of segments from find_hiatus(): " << dataset->find_hiatus() + 1 << std::endl;
    // std::cout << "Number of segments from segment_indexes.size(): " << dataset->get_segment_indexes_size() << std::endl;

    std::cout << "Segments vector size: " << segments.size() << std::endl;

    for (int i = 0; i < dataset->get_segment_indexes_size(); i++)
    {
        segments.push_back(TSegment(dataset, dataset->get_index(i).first, dataset->get_index(i).second));
        segments[i].copy_ages_to_segment();
        segments[i].copy_depths_to_segment();
    }

    std::cout << "Segments vector size: " << segments.size() << std::endl;

    segments[0].display_ages_vector();
    segments[0].display_depths_vector();

    dataset->~TData();

    return 0;
}
