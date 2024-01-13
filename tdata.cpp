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