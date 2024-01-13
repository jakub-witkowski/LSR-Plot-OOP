#ifndef TDATA_H
#define TDATA_H

#include <iostream>
#include <vector>
#include <string>

class TData
{
public:
    std::string filename{};

    TData(std::string);

    ~TData();

    void load_input();
    void display_raw_data();

    friend void display_member_vector_dbl(TData*, char);
    friend bool is_data_sorted(TData*, char);
    friend int find_hiatus(TData*);

/* setter functions */
    void set_raw_data(std::string);
    void set_ages(double);
    void set_depths(double);

/* getter functions */
    size_t get_raw_data_size();
    std::string get_raw_data(int);

private:
    std::vector<std::string> raw_data{};
    std::vector<double> ages{};
    std::vector<double> depths{};

};

#endif // TDATA_H
