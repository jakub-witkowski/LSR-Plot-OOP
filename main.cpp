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

    // std::unique_ptr<TData> dataset(new TData(argv[1]));
    TData * dataset = new TData(argv[1]);

    /* Test if data is sorted */
    if (!dataset->test_input_order())
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    dataset->load_input();
    dataset->find_hiatus();

    for (int i = 0; i < dataset->get_segment_indexes_size(); i++)
    {
        segments.push_back(TSegment(dataset, dataset->get_index(i).first, dataset->get_index(i).second));
        segments[i].copy_ages_to_segment();
        segments[i].copy_depths_to_segment();
        segments[i].set_g1_ptr();
        segments[i].compute_lsr_values();
        segments[i].set_g3_ptr();
    }

    for (int i = 0; i < segments.size(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            segments[i].add_to_fit_vector(j);
        }

        segments[i].perform_fitting();
        segments[i].get_fit_line_for_plot(segments[i].find_the_best_fit());
        segments[i].set_g2_ptr();
        segments[i].lsr_smoothing();
        segments[i].set_g4_ptr();
    }
        
    for (int i = 0; i < segments.size(); i++)
    {
        std::string fname = "segment" + std::to_string(i+1) + ".png";
        segments[i].plot_to_png(fname);
    }

    delete dataset;

    return 0;
}
