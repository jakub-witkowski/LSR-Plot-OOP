#include "tdata.h"
#include "tsegment.h"
#include "tplot.h"
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

    for (int i = 0; i < dataset->get_segment_indexes_size(); i++)
    {
        segments.push_back(TSegment(dataset, dataset->get_index(i).first, dataset->get_index(i).second));
        segments[i].copy_ages_to_segment();
        segments[i].copy_depths_to_segment();
        // segments[i].display_ages_vector();
        // segments[i].display_depths_vector();
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
        // std::cout << "Segment " << i << ": Ages vector size: " << segments[i].get_ages_vector_size() << std::endl;
    }
    
    std::unique_ptr<TPlot> plot(new TPlot());

    for (int i = 0; i < segments.size(); i++)
    {
        plot->set_segm_ptr(&segments[i]);
        // std::cout << "Segment " << i << ": Ages vector size: " << segments[i].get_ages_vector_size() << std::endl;
        plot->copy_ages_to_plot();
        plot->copy_depths_to_plot();
        plot->set_g1_ptr();
        plot->copy_fit_line_to_plot();
        plot->set_g2_ptr();
        plot->copy_lsr_plot_values_to_plot();
        plot->copy_lsr_plot_ages_to_plot();
        plot->set_g3_ptr();
        plot->copy_smoothed_lsr_plot_values_to_plot();
        plot->set_g4_ptr();
        // plot->display_ages_vector();
    }

    // std::cout << "Plot - ages vector size: " << plot->get_ages_vector_size() << std::endl;
    // std::cout << "Dataset - ages vector size: " << dataset->get_ages_vector_size() << std::endl;
    // dataset->display_ages_vector();

    /* determine the number of segments and plot the results */
    if (segments.size() == 1)
    {
        segments[0].plot_to_png("plot.png");
    }
    else if (segments.size() > 1)
    {
        plot->plot_to_png("plot.png");
    }

    delete dataset;

    return 0;
}
