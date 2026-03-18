#include "FourierDonusumu.hpp"
#include <cmath>

const double PI = std::acos(-1.0);

//Cooley-Tukey FFT algoritması
void FourierDonusumu::hesapla(std::vector<KarmasikSayi>& veriler) {
    int boyut = veriler.size();
    
    // Temel durum
    if (boyut <= 1) return;

    std::vector<KarmasikSayi> ciftler(boyut / 2);
    std::vector<KarmasikSayi> tekler(boyut / 2);

    // Diziyi çift ve tek indislere ayırır
    for (int i = 0; i < boyut / 2; ++i) {
        ciftler[i] = veriler[i * 2];
        tekler[i] = veriler[i * 2 + 1];
    }

    // Alt dizileri hesaplar
    hesapla(ciftler);
    hesapla(tekler);

    // Kelebek operasyonu birleştirme
    for (int i = 0; i < boyut / 2; ++i) {
        double aci = -2.0 * PI * i / boyut;
        KarmasikSayi dondurmeFaktoru(std::cos(aci), std::sin(aci));
        KarmasikSayi carpim = dondurmeFaktoru * tekler[i];

        veriler[i] = ciftler[i] + carpim;
        veriler[i + boyut / 2] = ciftler[i] - carpim;
    }
}