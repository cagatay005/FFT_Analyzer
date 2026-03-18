import numpy as np
import wave
import struct

def ozel_sinyal_uret(frekanslar, sure=3.0, ornekleme_hizi=44100, dosya_adi="ozel_test_sesi.wav"):
    print(f"\n[*] Bilesenleri {frekanslar} Hz olan ozel sinyal sentezleniyor...")
    
    # Zaman ekseni
    ornek_sayisi = int(sure * ornekleme_hizi)
    t = np.linspace(0, sure, ornek_sayisi, False)
    
    # bos dizi
    toplam_sinyal = np.zeros(ornek_sayisi)
    # sinyal ekleme
    for f in frekanslar:
        toplam_sinyal += np.sin(2 * np.pi * f * t)
        
    # Kırpılma önleme
    maksimum_genlik = np.max(np.abs(toplam_sinyal))
    if maksimum_genlik > 0:
        toplam_sinyal = (toplam_sinyal / maksimum_genlik) * 0.9
        
    # 16-bit PCM formatina cevirme C++ için
    sinyal_int = (toplam_sinyal * 32767).astype(np.int16)
    
    with wave.open(dosya_adi, 'w') as dosya:
        dosya.setnchannels(1)
        dosya.setsampwidth(2)
        dosya.setframerate(ornekleme_hizi)
        for s in sinyal_int:
            dosya.writeframes(struct.pack('<h', s))
            
    print(f"'{dosya_adi}' basariyla olusturuldu.")

if __name__ == "__main__":
    print("=== OZEL TEST SINYALI SENTEZLEYICI ===")
    print("Muziksel referanslar:")
    print("- Bas (Kalin): 60, 120, 250")
    print("- Orta (Insan Sesi): 500, 1000, 2000")
    print("- Tiz (Ince): 4000, 8000")
    
    girdi = input("\nUretmek istediginiz frekanslari virgulle ayirarak girin (Ornek: 440, 1200, 3500): ")
    
    try:
        secilen_frekanslar = [float(f.strip()) for f in girdi.split(',')]
        ozel_sinyal_uret(secilen_frekanslar)
    except ValueError:
        print("Hata: Lutfen sadece sayilari virgulle ayirarak girin.")