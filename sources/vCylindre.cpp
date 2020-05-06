#include "../headers/vCylindre.hpp"
#include <cmath>
#include <stdexcept>

vCylindre::vCylindre(std::string nom, std::string marque, float diametre, float profondeur) : diametre_(diametre), profondeur_(profondeur), vBagage(nom, marque) {

    this->volume_ = calculerVolume();
    if(this->volume_ < 0) throw std::range_error("ERREUR : Le volume du bagage ne peut pas être inférieur à 0.");
}

float vCylindre::calculerVolume() const {   

    // V = PI * R^2 * p cm^3, divisé par 1000 pour avoir en Litres.
    return (pow((this->diametre_ / 2), 2) * M_PI * this->profondeur_) / 1000;
}