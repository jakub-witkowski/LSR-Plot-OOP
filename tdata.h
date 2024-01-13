#ifndef TDATA_H
#define TDATA_H

//#include "tplot.h"

#include <iostream>
#include <vector>
#include <string>

class TData
{
public:
//    std::string *data_ptr{nullptr};

    std::string filename{};

    TData(std::string);

    ~TData();

    void load_input();

    friend void display_raw_data(TData*);
    friend void display_member_vector_dbl(TData*, char);
    friend bool is_data_sorted(TData*, char);
    friend int find_hiatus(TData*);

//    friend void TPlot::age_vs_depth_plot(TData*);

/* setter functions */
    void set_raw_data(std::string);
    void set_ages(double);
    void set_depths(double);

private:
    std::vector<std::string> raw_data{};
    std::vector<double> ages{};
    std::vector<double> depths{};

};

#endif // TDATA_H
