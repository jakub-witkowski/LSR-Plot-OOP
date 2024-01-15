#include "tdata.h"
#include "tsegment.h"
#include <iostream>

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

    dataset->load_input();
    dataset->find_hiatus();

    TSegment* seg = new TSegment(dataset, 0, 20);
    std::cout << "Dataset pointer: " << seg->get_dataset_ptr() << std::endl;
    seg->copy_ages_to_segment();
    seg->display_ages_vector();
    seg->copy_depths_to_segment();
    seg->display_depths_vector();

    // dataset->display_raw_data();
    // dataset->display_ages_vector();
    // dataset->display_depths_vector();
    // dataset->display_segment_indexes_vector();

    /* Test if data is sorted */
    if (!dataset->test_input_order())
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    // std::cout << "Number of segments from find_hiatus(): " << dataset->find_hiatus() + 1 << std::endl;
    // std::cout << "Number of segments from segment_indexes.size(): " << dataset->get_segment_indexes_size() << std::endl;

    //dataset->create_segments(dataset, segments);

    std::cout << "Segments vector size: " << segments.size() << std::endl;

    dataset->~TData();
    seg->~TSegment();

    return 0;
}
