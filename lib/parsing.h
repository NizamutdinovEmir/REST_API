#ifndef CPR_EXAMPLE_PARSING_H
#define CPR_EXAMPLE_PARSING_H
#include "iostream"
#include "vector"
#include "string"
#include "cstring"
#include <sstream>
#include <iomanip>

#pragma once

struct data_base {
    std::string name_valute;
    std::string Date_Current;
    std::string file_name = "test";
    std::string Dates;
    double nominal_valute = 1.00;
    bool check_name_valute = false;
    bool check_Date_Current = false;
    bool check_file_name = false;
    bool check_Dates = false;
    bool check_nominal_valute = false;
};



void Parsing_Arg(int argc , char** argv , data_base& Data_base);




#endif //CPR_EXAMPLE_PARSING_H
