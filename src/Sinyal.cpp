#include "Sinyal.hpp"
#include <cmath>

const double PI = std::acos(-1.0);

// Sınıfı örnekleme frekansıyla ilklendirir
Sinyal::Sinyal(int frekans) : orneklemeFrekansi(frekans) {}

// Gerçel sayıyı karmaşık sayıya çevirip listeye ekler
void Sinyal::veriEkle(double deger) {
    veriler.push_back(KarmasikSayi(deger, 0.0));
}

// Karmaşık sayı dizisini döndürür
std::vector<KarmasikSayi> Sinyal::verileriGetir() const {
    return veriler;
}

// Dizinin uzunluğunu verir
int Sinyal::boyut() const {
    return veriler.size();
}

// Belirtilen frekans ve sürede sinüs dalgası oluşturur
void Sinyal::testSinusOlustur(double dalgaFrekansi, double genlik, double sure) {
    int ornekSayisi = sure * orneklemeFrekansi;
    for (int i = 0; i < ornekSayisi; ++i) {
        double zaman = static_cast<double>(i) / orneklemeFrekansi;
        double deger = genlik * std::sin(2.0 * PI * dalgaFrekansi * zaman);
        veriEkle(deger);
    }
}