#include <iostream>
#include <string>
#include "Sinyal.hpp"
#include "FourierDonusumu.hpp"
#include "WavOkuyucu.hpp"
#include "SonucYazici.hpp"

int main() {
    // Standart CD kalitesi
    int orneklemeFrekansi = 44100;
    int fftBoyutu = 65536; 
    
    Sinyal sinyal(orneklemeFrekansi);
    std::string girisDosyasi = "test_sesi.wav";
    std::string cikisDosyasi = "fft_sonuc.csv";

    std::cout << "WAV dosyasi okunuyor: " << girisDosyasi << "..." << std::endl;

    // WAV dosyasından verileri okur
    if (!WavOkuyucu::oku(girisDosyasi, sinyal, fftBoyutu)) {
        return 1;
    }

    std::vector<KarmasikSayi> veriler = sinyal.verileriGetir();

    std::cout << "FFT hesaplaniyor (" << fftBoyutu << " orneklem)..." << std::endl;

    // Sinyali frekans düzlemine çevirir
    FourierDonusumu::hesapla(veriler);

    std::cout << "Sonuclar CSV dosyasina yaziliyor..." << std::endl;

    // Sonuçları dışa aktarır
    if (SonucYazici::csvYaz(cikisDosyasi, veriler, orneklemeFrekansi)) {
        std::cout << "Islem basariyla tamamlandi. Cikti: " << cikisDosyasi << std::endl;
    }

    return 0;
}