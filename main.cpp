#include "tdata.h"
#include "tsegment.h"
#include "tplot.h"
#include <iostream>

std::vector<TSegment> segments{}; // vector holding class TSegment objects
bool is_overfitted{false}; // auxiliary variable used for testing whether the fit line is overfitted

int main(int argc, char** argv)
{
    if (!argv[1])
    {
        std::cout << "No filename given!" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* An object of class TData holds the input data from the file */
    TData * dataset = new TData(argv[1]);

    /* Test if data is sorted */
    if (!dataset->test_input_order())
    {
        std::cout << "The data is not properly sorted; inspect the file: " << dataset->filename << " and try again." << std::endl;
        exit(EXIT_FAILURE);
    }

    dataset->load_input();
    dataset->find_hiatus();

    /* Depending on the number of hiatuses in the dataset (n), n+1 objects of class TSegment are created.
    Data are copied to each segment, and linear sedimentation rates are calculated based on raw data */
    for (int i = 0; i < dataset->get_segment_indexes_size(); i++)
    {
        segments.push_back(TSegment(dataset, dataset->get_index(i).first, dataset->get_index(i).second));
        segments[i].copy_ages_to_segment();
        segments[i].copy_depths_to_segment();
        segments[i].set_g1_ptr();
        segments[i].compute_lsr_values();
        segments[i].set_g3_ptr();
    }

    /* polynomial functions are created for each segment, the one displaying the best fit is selected 
    by finding the lowest chi2/ndf ratio; the selected fit line is then tested for overfitting; if it
    is found to be overfitted to the dataset, the next best fit is selected */
    for (int i = 0; i < segments.size(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            segments[i].add_to_fit_vector(j);
        }

        segments[i].perform_fitting();
        segments[i].get_fit_line_for_plot(segments[i].find_the_best_fit(0));
        
        is_overfitted = segments[i].test_for_overfitting();
        int index{1};
        while (is_overfitted == true)
        {
            segments[i].clear_fit_line_vector();
            segments[i].get_fit_line_for_plot(segments[i].find_the_best_fit(index));
            index++;
            is_overfitted = segments[i].test_for_overfitting();
        }

        /* linear sedimentation rates are smoothed using the selected polynomial fit */
        segments[i].set_g2_ptr();
        segments[i].lsr_smoothing();
        segments[i].set_g4_ptr();
    }
    
    /* determine the number of segments and plot the results */
    if (segments.size() == 1)
    {
        segments[0].plot_to_png("plot.png");
    }
    else if (segments.size() > 1)
    {
        std::unique_ptr<TPlot> plot(new TPlot());

        for (int i = 0; i < segments.size(); i++)
        {
            plot->set_segm_ptr(&segments[i]);
            plot->copy_ages_to_plot();
            plot->copy_depths_to_plot();
            plot->set_g1_ptr();
            plot->copy_fit_line_to_plot();
            plot->set_g2_ptr();

            /* modifications to the data vectors to reflect hiatuses between segments */
            if (segments.size() > 1)
                if ((i > 0) && (i <= segments.size() - 1))
                    plot->set_lsr_plot_values(0);

            plot->copy_lsr_plot_values_to_plot();

            if (segments.size() > 1)
                if ((i >= 0) && (i < segments.size() - 1))
                    plot->set_lsr_plot_values(0);

            if (segments.size() > 1)
                if ((i > 0) && (i <= segments.size() - 1))
                    plot->set_lsr_plot_ages(segments[i].get_lsr_plot_age(0)); // repeat first element from the segment to be copied

            plot->copy_lsr_plot_ages_to_plot();

            if (segments.size() > 1)
                if ((i >= 0) && (i < segments.size() - 1))
                    plot->set_lsr_plot_ages(plot->get_lsr_plot_age(plot->get_lsr_ages_vector_size() - 1));

            plot->set_g3_ptr();

            if (segments.size() > 1)
                if ((i > 0) && (i <= segments.size() - 1))
                    plot->set_smoothed_lsr_plot_values(0);

            plot->copy_smoothed_lsr_plot_values_to_plot();

            if (segments.size() > 1)
                if ((i >= 0) && (i < segments.size() - 1))
                    plot->set_smoothed_lsr_plot_values(0);

            plot->set_g4_ptr();
        }

        plot->plot_to_png("plot.png");
    }

    delete dataset;

    return 0;
}
