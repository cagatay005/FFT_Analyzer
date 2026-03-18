#include "KarmasikSayi.hpp"
#include <cmath>

KarmasikSayi::KarmasikSayi(double g, double s) : gercel(g), sanal(s) {}

KarmasikSayi KarmasikSayi::operator+(const KarmasikSayi& diger) const {
    return KarmasikSayi(gercel + diger.gercel, sanal + diger.sanal);
}

KarmasikSayi KarmasikSayi::operator-(const KarmasikSayi& diger) const {
    return KarmasikSayi(gercel - diger.gercel, sanal - diger.sanal);
}

KarmasikSayi KarmasikSayi::operator*(const KarmasikSayi& diger) const {
    return KarmasikSayi(
        (gercel * diger.gercel) - (sanal * diger.sanal),
        (gercel * diger.sanal) + (sanal * diger.gercel)
    );
}

double KarmasikSayi::buyukluk() const {
    return std::sqrt((gercel * gercel) + (sanal * sanal));
}