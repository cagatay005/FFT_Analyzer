#ifndef SINYAL_HPP
#define SINYAL_HPP

#include <vector>
#include "KarmasikSayi.hpp"

class Sinyal {
private:
    std::vector<KarmasikSayi> veriler;
    int orneklemeFrekansi;

public:
    Sinyal(int frekans);
    void veriEkle(double deger);
    std::vector<KarmasikSayi> verileriGetir() const;
    int boyut() const;
    void testSinusOlustur(double dalgaFrekansi, double genlik, double sure);
};

#endif