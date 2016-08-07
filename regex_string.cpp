namespace regex_string {
        std::regex HDD_len{ R"(([[:s:]][23].5))" };
        std::regex HDD_speed{ R"(([[:s:]][0-9]{4,}R))" };
        std::regex storage_cap{ R"(([[:s:]][0-9]{3,}G)|([0-9](\.[0-9])?T))" };
        std::regex CPU_model{ R"(([IE][0-9][-_][0-9]{3,}[A-Z]*)|)"
                        R"((\/[A-Z]+[0-9]{3,}[A-Z]*))" };
        std::regex adapter_watt{ R"(([[:s:]][0-9]+W))" };
        std::regex adapter_volt{ R"(([[:s:]][0-9]+(\.[0-9])?V))" };
        std::regex LCD_size { R"(([[:s:]][0-9]+(\.[0-9])?))" };
        std::regex DDR_speed { R"(([[:s:]][0-9]{3,}[^pP]))" };
        std::regex DDR_size { R"(([[:s:]][0-9]+G))" };
}
