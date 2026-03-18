#ifndef WAV_OKUYUCU_HPP
#define WAV_OKUYUCU_HPP

#include <string>
#include "Sinyal.hpp"

class WavOkuyucu {
public:
    // WAV dosyasından belirtilen boyutta örneklem okuyup sinyale ekler
    static bool oku(const std::string& dosyaYolu, Sinyal& sinyal, int ornekSayisi = 65536);
};

#endif