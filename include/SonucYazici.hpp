#ifndef SONUC_YAZICI_HPP
#define SONUC_YAZICI_HPP

#include <string>
#include <vector>
#include "KarmasikSayi.hpp"

class SonucYazici {
public:
    // FFT sonuçlarını frekans ve genlik olarak CSV dosyasına kaydeder
    static bool csvYaz(const std::string& dosyaYolu, const std::vector<KarmasikSayi>& veriler, int orneklemeFrekansi);
};

#endif