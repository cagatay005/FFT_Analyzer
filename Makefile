CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDES = -I./include
SRCS = src/main.cpp src/KarmasikSayi.cpp src/Sinyal.cpp src/FourierDonusumu.cpp src/WavOkuyucu.cpp src/SonucYazici.cpp
TARGET = fft_analizoru

# Projeyi derler
all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

# Derlenmiş dosyayı siler
clean:
	rm -f $(TARGET)