#include "../headers/vDemiSphere.hpp"
#include <cmath>
#include <stdexcept>

vDemiSphere::vDemiSphere(std::string nom, std::string marque, float diametre) : diametre_(diametre), vBagage(nom, marque) {

    this->volume_ = calculerVolume();
    if(this->volume_ < 0) throw std::range_error("ERREUR : Le volume du bagage ne peut pas être inférieur à 0.");
}

float vDemiSphere::calculerVolume() const {   

    // V = 4/3 * 1/2 * PI * R^3 cm^3, divisé par 1000 pour avoir en litres.
    return (pow((this->diametre_ / 2), 3) * M_PI * 4) / 6000;
}