#include "WavOkuyucu.hpp"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>

// WAV baslik yapisini (header) temsil eden struct
struct WavDosyaVerisi {
    char        riff_chunk_id[4];   // "RIFF" olmali
    uint32_t    chunk_size;
    char        format[4];          // "WAVE" olmali
    char        fmt_chunk_id[4];    // "fmt " olmali
    uint32_t    fmt_chunk_size;
    uint16_t    audio_format;       // 1 = PCM olmali
    uint16_t    num_channels;       // 1 = Mono olmali
    uint32_t    sample_rate;        // Ornekleme hizi
    uint32_t    byte_rate;
    uint16_t    block_align;
    uint16_t    bits_per_sample;    // 16 bit olmali
    char        data_chunk_id[4];   // "data" olmali
    uint32_t    data_chunk_size;
};

// WAV dosyasini basligina bakarak dogrular ve verileri okur
bool WavOkuyucu::oku(const std::string& dosyaYolu, Sinyal& sinyal, int ornekSayisi) {
    std::ifstream dosya(dosyaYolu, std::ios::binary);
    if (!dosya.is_open()) {
        std::cerr << "Hata: WAV dosyasi acilamadi -> " << dosyaYolu << std::endl;
        return false;
    }

    WavDosyaVerisi baslik;
    // Basligi (ilk 44 bayti) struct'a okur
    dosya.read(reinterpret_cast<char*>(&baslik), sizeof(WavDosyaVerisi));

    // --- Dogrulama Kontrolleri ---
    std::string riff_id(baslik.riff_chunk_id, 4);
    std::string wave_id(baslik.format, 4);
    if (riff_id != "RIFF" || wave_id != "WAVE") {
        std::cerr << "Hata: Gecersiz WAV dosyasi formati." << std::endl;
        return false;
    }

    if (baslik.num_channels != 1) {
        std::cerr << "Hata: Dosya Mono degil (" << baslik.num_channels << " kanal)." << std::endl;
    }

    if (baslik.bits_per_sample != 16) {
        std::cerr << "Hata: Dosya 16-bit degil (" << baslik.bits_per_sample << " bit)." << std::endl;
    }

    std::cout << "WAV Dosyasi Dogrulandi: " << baslik.sample_rate << " Hz, " 
              << baslik.bits_per_sample << "-bit, Mono" << std::endl;

    // Veri kismine atlar
    std::string data_id(baslik.data_chunk_id, 4);
    if (data_id != "data") {
        // bazi WAV'larda data'dan once baska chunkları arar
        char ara_bayt;
        bool data_bulundu = false;
        for (int i=0; i < 1000; ++i) { // yeterli
            if (dosya.read(&ara_bayt, 1) && ara_bayt == 'd') {
                char temp[3];
                if (dosya.read(temp, 3) && temp[0] == 'a' && temp[1] == 't' && temp[2] == 'a') {
                    dosya.read(reinterpret_cast<char*>(&baslik.data_chunk_size), 4);
                    data_bulundu = true;
                    break;
                }
            }
        }
        if (!data_bulundu) {
            std::cerr << "Hata: WAV verisi (data chunk) bulunamadi." << std::endl;
            return false;
        }
    }

    int16_t orneklem;
    int okunan = 0;

    // Binary veriyi 16-bitlik parcalar halinde okur
    while (okunan < ornekSayisi && dosya.read(reinterpret_cast<char*>(&orneklem), sizeof(int16_t))) {
        // 16-bit tam sayiyi normalize edip (-1.0 ile 1.0 arasina) sinyale ekler
        double normalizeDeger = static_cast<double>(orneklem) / 32768.0;
        sinyal.veriEkle(normalizeDeger);
        okunan++;
    }

    dosya.close();
    
    // Zero-padding
    while (okunan < ornekSayisi) {
        sinyal.veriEkle(0.0);
        okunan++;
    }

    return true;
}