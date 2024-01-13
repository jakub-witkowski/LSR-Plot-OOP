#include "tdata.h"
//#include "tplot.h"
#include "functions.h"
#include <iostream>
//#include "tsegment.h"

int number_of_segments{};
//std::vector<TSegment*>segments{};

int main(int argc, char** argv)
{
    if (!argv[1])
    {
        std::cout << "No filename given!" << std::endl;
        exit(EXIT_FAILURE);
    }

    TData * dataset = new TData(argv[1]);

    dataset->load_input();
    //display_raw_data(dataset);
    //display_member_vector_dbl(dataset, 'a');

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

//    TPlot * plot = new TPlot();

//    plot->age_vs_depth_plot(dataset);

//    number_of_segments = find_hiatus(dataset) + 1;

/*    if (number_of_segments == 0)
    {
        TSegment * segment = new TSegment();
    }
    else
    {
        number_of_segments = find_hiatus(dataset) + 1;
        for (int i = 0; i < number_of_segments; i++)
        {
            segments[i] = new TSegment();
        }
    }*/

    //auto value = *(dataset->data_ptr);
    //std::cout << "Number of segments: " << number_of_segments + 1 << std::endl;
    //std::cout << "Size of dataset: " << sizeof(dataset) <<std::endl;
    dataset->~TData();
//    plot->~TPlot();

    return 0;
}
