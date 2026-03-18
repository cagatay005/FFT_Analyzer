#ifndef VERI_OKUYUCU_HPP
#define VERI_OKUYUCU_HPP

#include <string>
#include "Sinyal.hpp"

class VeriOkuyucu {
public:
    // CSV dosyasındaki değerleri okuyup sinyale ekler
    static bool csvOku(const std::string& dosyaYolu, Sinyal& sinyal);
};

#endif