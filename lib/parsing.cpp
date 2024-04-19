#include "parsing.h"


void Parsing_Arg(int argc , char** argv, data_base& Data_base) {
    setlocale(0, "");
    for (int i = 1; i < argc;++i) {
        std::string argument = argv[i];
        if (argument.substr(0 , 8) == "--Vname=") {
            Data_base.name_valute = argument.substr(8);
            Data_base.check_name_valute = true;
        } else if (argument.substr(0 , 7) == "--Vnom=") {
            Data_base.nominal_valute = std::stoi(argument.substr(7));
            Data_base.check_nominal_valute = true;
        } else if (argument.substr(0 , 7) == "--Date=") {
            Data_base.Date_Current = argument.substr(7);
            Data_base.check_Date_Current = true;
        } else if (argument.substr(0 , 11) == "--DateDate=") {
            Data_base.Dates = argument.substr(11);
            Data_base.check_Dates = true;
        } else if (argument.substr(0 , 11) == "--FileName=") {
            Data_base.file_name = argument.substr(11);
            Data_base.check_file_name = true;
        }
    }
    if (!Data_base.check_name_valute) {
        std::cerr << "Missing Name Valute" << std::endl;
    }
}