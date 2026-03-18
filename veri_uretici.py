import math
import csv

ornekleme_frekansi = 64  # FFT için 2'nin kuvveti (2^6)
sure = 1.0
ornek_sayisi = int(ornekleme_frekansi * sure)

with open('veri.csv', 'w', newline='') as dosya:
    yazici = csv.writer(dosya)
    for i in range(ornek_sayisi):
        zaman = i / ornekleme_frekansi
        # 5 Hz (1 Genlik) ve 15 Hz (0.5 Genlik) sinyalleri birleştirir
        deger = math.sin(2 * math.pi * 5 * zaman) + 0.5 * math.sin(2 * math.pi * 15 * zaman)
        yazici.writerow([deger])

print("veri.csv dosyasi basariyla olusturuldu.")