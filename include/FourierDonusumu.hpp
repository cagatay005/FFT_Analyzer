#ifndef FOURIER_DONUSUMU_HPP
#define FOURIER_DONUSUMU_HPP

#include <vector>
#include "KarmasikSayi.hpp"

class FourierDonusumu {
public:
    // Sinyali frekans düzlemine çevirir
    static void hesapla(std::vector<KarmasikSayi>& veriler);
};

#endif