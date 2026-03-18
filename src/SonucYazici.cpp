#include "SonucYazici.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

// Frekans ve genlik verilerini dosyaya yazar
bool SonucYazici::csvYaz(const std::string& dosyaYolu, const std::vector<KarmasikSayi>& veriler, int orneklemeFrekansi) {
    std::ofstream dosya(dosyaYolu);
    if (!dosya.is_open()) {
        std::cerr << "Hata: Cikti dosyasi olusturulamadi -> " << dosyaYolu << std::endl;
        return false;
    }

    dosya << "Frekans,Genlik\n";
    
    int n = veriler.size();
    
    // Sadece Nyquist frekansına (n/2) kadar olan yararlı kısmı kaydeder
    for (int i = 0; i < n / 2; ++i) {
        // Gerçek frekans değerini Hz cinsinden hesaplar
        double frekans = static_cast<double>(i * orneklemeFrekansi) / n;
        
        // Genliği gerçek değerine normalize eder
        double genlik = veriler[i].buyukluk() / (n / 2.0);
        if (i == 0) genlik = veriler[0].buyukluk() / n;

        dosya << std::fixed << std::setprecision(5) << frekans << "," << genlik << "\n";
    }

    dosya.close();
    return true;
}