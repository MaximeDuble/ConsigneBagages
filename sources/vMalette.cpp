#include "../headers/vMalette.hpp"
#include <stdexcept>

vMalette::vMalette(std::string nom, std::string marque, float longueur, float largeur, float profondeur) : longueur_(longueur), largeur_(largeur), profondeur_(profondeur), vBagage(nom, marque) {

    this->volume_ = calculerVolume();
    if(this->volume_ < 0) throw std::range_error("ERREUR : Le volume du bagage ne peut pas être inférieur à 0.");
}

float vMalette::calculerVolume() const {

    // V = L * l * p cm^3, divisé par 1000 pour obtenir en Litres.
    return (this->longueur_ * this->largeur_ * this->profondeur_) / 1000;
}