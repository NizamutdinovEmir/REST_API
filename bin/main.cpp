#include <iostream>
#include <string>
#include "../lib/pugixml.hpp"
#include "../lib/parsing.h"
#include "../lib/valute.h"




int main(int argc , char** argv) {
    setlocale(0, "");
    data_base Data_info;
    // URL для запроса данных с сайта
    setup(argc , argv, Data_info);

    return 0;
}
