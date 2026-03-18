import subprocess
import sys
import os
import csv
import tkinter as tk
from tkinter import filedialog
import pyqtgraph as pg
from PyQt5 import QtWidgets

GECICI_WAV = "test_sesi.wav"
GECICI_CSV = "fft_sonuc.csv"

def eski_verileri_temizle():
    # Eski kalıntıları silme
    for dosya in [GECICI_WAV, GECICI_CSV]:
        if os.path.exists(dosya):
            os.remove(dosya)
            print(f"[*] Eski dosya temizlendi: {dosya}")

def youtube_ses_indir(youtube_url):
    print("YouTube'dan ses indiriliyor...")
    komut = [
        sys.executable, "-m", "yt_dlp",
        "--force-overwrites",
        "-x", "--audio-format", "wav",
        "--postprocessor-args", "-ac 1 -ar 44100",
        "-o", GECICI_WAV, youtube_url
    ]
    subprocess.run(komut, check=True)
    print("WAV dosyasi hazir.")
    return True

def yerel_dosya_sec_ve_donustur():
    # Tkinter ı kapatır dosya seçiciyi açar
    root = tk.Tk()
    root.withdraw()
    
    dosya_yolu = filedialog.askopenfilename(
        title="Analiz Edilecek Medya Dosyasini Secin",
        filetypes=[("Tum Medya Dosyalari", "*.*"), ("Ses", "*.mp3 *.wav"), ("Video", "*.mp4 *.mkv")]
    )
    
    if not dosya_yolu:
        print("Dosya secimi iptal edildi.")
        return False

    print(f"'{os.path.basename(dosya_yolu)}' isleniyor ve formati ayarlaniyor...")
    komut = [
        "ffmpeg", "-y", "-i", dosya_yolu,
        "-ac", "1", "-ar", "44100", "-sample_fmt", "s16",
        GECICI_WAV
    ]
    subprocess.run(komut, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
    print("WAV dosyasi hazir.")
    return True

def cpp_analizoru_calistir(calistirilabilir_dosya="./fft_analizoru"):
    print("C++ FFT motoru calistiriliyor...")
    subprocess.run([calistirilabilir_dosya], check=True)
    print("Matematiksel analiz tamamlandi.")

def masaustu_grafik_ciz():
    if not os.path.exists(GECICI_CSV):
        print("Hata: Analiz sonucu bulunamadi! C++ motoru calismamis olabilir.")
        return
        
    frekanslar, genlikler = [], []
    print("Grafik penceresi baslatiliyor...")
    
    with open(GECICI_CSV, 'r') as dosya:
        okuyucu = csv.reader(dosya)
        next(okuyucu)
        for satir in okuyucu:
            frekanslar.append(float(satir[0]))
            genlikler.append(float(satir[1]))

    uygulama = QtWidgets.QApplication(sys.argv)
    pencere = pg.PlotWidget(title="FFT Spektrum Analizörü")
    pencere.resize(1200, 700)
    pencere.setBackground('#0d0d0d')
    
    pencere.setLabel('left', 'Genlik (Amplitud)', color='#ffffff', size='12pt')
    pencere.setLabel('bottom', 'Frekans (Hz)', color='#ffffff', size='12pt')
    pencere.showGrid(x=True, y=True, alpha=0.2)
    pencere.setXRange(0, 5000, padding=0) 
    
    kalem = pg.mkPen(color='#00ffcc', width=1.5)
    pencere.plot(frekanslar, genlikler, pen=kalem)
    
    pencere.show()
    sys.exit(uygulama.exec_())

if __name__ == "__main__":
    print("=== FFT SES ANALIZ MOTORU ===")
    print("1. YouTube Linki Gir")
    print("2. Bilgisayardan Dosya Sec (MP3, MP4, WAV vb.)")
    secim = input("Seciminiz (1/2): ")

    try:
        eski_verileri_temizle()
        
        islem_basarili = False
        if secim == '1':
            url = input("YouTube URL: ")
            islem_basarili = youtube_ses_indir(url)
        elif secim == '2':
            islem_basarili = yerel_dosya_sec_ve_donustur()
        else:
            print("Gecersiz secim.")

        if islem_basarili:
            cpp_analizoru_calistir()
            masaustu_grafik_ciz()
            
    except Exception as e:
        print(f"Bir hata olustu: {e}")