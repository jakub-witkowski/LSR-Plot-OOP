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

bool TData::is_ages_vector_sorted()
{
    bool result{true};

    for (int i = 1; i < get_ages_vector_size(); i++)
    {
        if (get_ages(i) < get_ages(i-1))
            result = false;
    }

    return result;
}

bool TData::is_depths_vector_sorted()
{
    bool result{true};

    for (int i = 1; i < get_depths_vector_size(); i++)
    {
        if (get_depths(i) < get_depths(i-1))
            result = false;
    }

    return result;
}

bool TData::test_input_order()
{
    bool a = is_ages_vector_sorted();
    bool d = is_depths_vector_sorted();
    return ((a == true) && (d == true) ? true : false);
}

int TData::find_hiatus()
{
    int number_of_hiatuses{};

    for (int i = 1; i < this->get_depths_vector_size(); i++)
    {
        if (this->get_depths(i) == this->get_depths(i-1))
            number_of_hiatuses++;
    }

    return number_of_hiatuses;
}

/* getter functions */
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

/* setter functions */
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