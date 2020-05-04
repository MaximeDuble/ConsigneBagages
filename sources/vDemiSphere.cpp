#include "../headers/vDemiSphere.hpp"
#include <cmath>

vDemiSphere::vDemiSphere(std::string nom, std::string marque, float diametre) : diametre_(diametre), vBagage(nom, marque) {

    this->volume_ = calculerVolume();
}

float vDemiSphere::calculerVolume() const {   

    // V = 4/3 * 1/2 * PI * R^3 cm^3, divisé par 1000 pour avoir en litres.
    return (pow((this->diametre_ / 2), 3) * M_PI * 4) / 6000;
}