#include "tdata.h"

#include <fstream>
#include <string>

TData::TData(std::string f) : filename(f)
{
    std::cout << "TData Constructor" << std::endl;
}

TData::~TData()
{
    std::cout << "TData Destructor" << std::endl;    
}

/* reads the dataset from the file and stores it in the raw_data vector */
void TData::load_input()
{
    std::ifstream input{filename};

    for (std::string line; std::getline(input, line);)
    {
        set_raw_data(line);
    }

    /* Separate data on coma, convert substring to double and copy to the respective depths or ages vector */
    for (int i = 0; i < raw_data.size(); i++)
    {
        size_t pos = raw_data[i].find(",");
        set_depths(stod(raw_data[i].substr(0, pos)));
        set_ages(stod(raw_data[i].substr(pos + 1)));
    }

//    data_ptr = &raw_data[0];
}

void TData::display_raw_data()
{
    std::cout << "Data in the raw_data vector: " << std::endl;
    for (int i = 0; i < get_raw_data_size(); i++)
    {
        std::cout << get_raw_data(i) << std::endl;
    }
}

void TData::display_ages_vector()
{
    std::cout << "Data in the ages vector: " << std::endl;
    for (int i = 0; i < get_ages_vector_size(); i++)
    {
        std::cout << get_ages(i) << std::endl;
    }
}

void TData::display_depths_vector()
{
    std::cout << "Data in the depths vector: " << std::endl;
    for (int i = 0; i < get_depths_vector_size(); i++)
    {
        std::cout << get_depths(i) << std::endl;
    }
}

size_t TData::get_raw_data_size()
{
    return this->raw_data.size();
}

size_t TData::get_ages_vector_size()
{
    return this->ages.size();
}

size_t TData::get_depths_vector_size()
{
    return this->depths.size();
}

std::string TData::get_raw_data(int i)
{
    return this->raw_data[i];
}

double TData::get_ages(int i)
{
    return this->ages[i];
}

double TData::get_depths(int i)
{
    return this->depths[i];
}

/* sets the value of a vector row */
void TData::set_raw_data(std::string l)
{
    this->raw_data.push_back(l);
}

void TData::set_ages(double a)
{
    this->ages.push_back(a);
}

void TData::set_depths(double d)
{
    this->depths.push_back(d);
}