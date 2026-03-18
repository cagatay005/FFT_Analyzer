#include "VeriOkuyucu.hpp"
#include <fstream>
#include <iostream>

// Dosyayı satır satır okur ve gerçel değer olarak kaydeder
bool VeriOkuyucu::csvOku(const std::string& dosyaYolu, Sinyal& sinyal) {
    std::ifstream dosya(dosyaYolu);
    if (!dosya.is_open()) {
        std::cerr << "Hata: Dosya acilamadi -> " << dosyaYolu << std::endl;
        return false;
    }

    std::string satir;
    while (std::getline(dosya, satir)) {
        try {
            // Metni ondalıklı sayıya çevirir
            double deger = std::stod(satir);
            sinyal.veriEkle(deger);
        } catch (...) {
            // Sayı olmayan satırları atlar
            continue;
        }
    }

    dosya.close();
    return true;
}