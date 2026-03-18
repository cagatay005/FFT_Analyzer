#ifndef KARMASIK_SAYI_HPP
#define KARMASIK_SAYI_HPP

class KarmasikSayi {
public:
    double gercel;
    double sanal;
    KarmasikSayi(double g = 0.0, double s = 0.0);
    KarmasikSayi operator+(const KarmasikSayi& diger) const;
    KarmasikSayi operator-(const KarmasikSayi& diger) const;
    KarmasikSayi operator*(const KarmasikSayi& diger) const;
    
    double buyukluk() const;
};

#endif