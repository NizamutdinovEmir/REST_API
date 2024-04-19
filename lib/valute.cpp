#include "valute.h"


void setup(int argc, char** argv , data_base& Data_base) {
    setlocale(0, "RU");
    Parsing_Arg(argc, argv, Data_base);
    std::ofstream fout;
    fout.open("C:/Users/emirn/CLionProjects/restapi/" + Data_base.file_name + ".txt");
    if (Data_base.check_Dates) {
        std::string url_for_id = "https://www.cbr.ru/scripts/XML_daily.asp";
        std::string Valute_ID;
        std::string name;
        auto response = cpr::Get(cpr::Url{url_for_id});
        // Проверка успешности запроса
        if (response.status_code == 200) {
            // Парсинг XML данных
            pugi::xml_document doc;
            if (doc.load_string(response.text.c_str())) {
                // Итерация по элементам в XML
                for (pugi::xml_node valute = doc.child("ValCurs").child("Valute"); valute; valute = valute.next_sibling(
                        "Valute")) {
                    std::string charCode = valute.child_value("CharCode");
                    if (charCode == Data_base.name_valute) {
                        name = valute.child_value("Name");
                        Valute_ID = valute.attribute("ID").value();
                        break; // Добавлен выход из цикла при нахождении нужного Valute
                    }
                }
            }
        }
        if (!Valute_ID.empty()) {
            std::string Date_start = Data_base.Dates.substr(0 , 10);
            std::string Date_finish = Data_base.Dates.substr(11);
            std::string url = "https://www.cbr.ru/scripts/XML_dynamic.asp";
            url = url + "?date_req1=" + Date_start + "&date_req2=" + Date_finish + "&VAL_NM_RQ=" + Valute_ID;


            response = cpr::Get(cpr::Url{url});
            // Проверка успешности запроса
            if (response.status_code == 200) {
                // Парсинг XML данных
                pugi::xml_document doc;
                if (doc.load_string(response.text.c_str())) {
                    // Итерация по узлам ValCurs
                    for (pugi::xml_node valcurs = doc.child("ValCurs"); valcurs; valcurs = valcurs.next_sibling("ValCurs")) {
                        // Итерация по узлам Record внутри каждого ValCurs
                        for (pugi::xml_node record = valcurs.child("Record"); record; record = record.next_sibling("Record")) {
                            std::string Date_now = record.attribute("Date").value();
                            double value = std::stod(record.child_value("Value"));
                            std::cout << Data_base.name_valute << " " << value << " " << Date_now << " " <<  value * (Data_base.nominal_valute) <<  std::endl;
                            if (Data_base.check_file_name) {
                                fout << Data_base.name_valute << " " << value << " " << Date_now << " " <<  value * (Data_base.nominal_valute) <<  std::endl;
                            }

                        }
                    }
                }
            } else {
                std::cerr << "Ошибка при выполнении запроса: " << response.status_code << std::endl;
            }
        } else {
            std::cerr << "Valute ID не найден" << std::endl;
        }
    } else {
            std::string url = "https://www.cbr.ru/scripts/XML_daily.asp";

            Data_base.check_Date_Current = true;
            if (Data_base.check_Date_Current) {
                url += "?date_req=" + Data_base.Date_Current;
            }
            // Выполнение HTTP запроса и получение данных с сайта
            auto response = cpr::Get(cpr::Url{url});
            // Проверка успешности запроса
            if (response.status_code == 200) {
                // Парсинг XML данных
                pugi::xml_document doc;
                if (doc.load_string(response.text.c_str())) {
                    // Итерация по элементам в XML
                    for (pugi::xml_node valute = doc.child("ValCurs").child(
                            "Valute"); valute; valute = valute.next_sibling("Valute")) {
                        std::string charCode = valute.child_value("CharCode");
                        if (charCode == Data_base.name_valute) {
                            std::string name = valute.child_value("Name");
                            Data_base.Date_Current = doc.child("ValCurs").attribute("Date").value();
                            double value = std::stod(valute.child_value("VunitRate"));
                            //std::cout << "CharCode: " << charCode << ", Name: " << name << ", Value: " << value * (Data_base.nominal_valute) << std::endl;
                            std::cout << Data_base.name_valute << " " << Data_base.nominal_valute << " " << Data_base.Date_Current << " " <<  value * (Data_base.nominal_valute);
                            if (Data_base.check_file_name) {
                                fout << Data_base.name_valute << " " << Data_base.nominal_valute << " " << Data_base.Date_Current << " " <<  value * (Data_base.nominal_valute) <<  std::endl;
                            }
                        }
                    }
                } else {
                    std::cerr << "error1" << std::endl;
                }
            } else {
                std::cerr << "error2: " << response.status_code << std::endl;
            }
    }
}