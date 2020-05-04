#include "../headers/vMalette.hpp"

vMalette::vMalette(std::string nom, std::string marque, float longueur, float largeur, float profondeur) : longueur_(longueur), largeur_(largeur), profondeur_(profondeur), vBagage(nom, marque) {

    this->volume_ = calculerVolume();
}

float vMalette::calculerVolume() const {

    // V = L * l * p cm^3, divisé par 1000 pour obtenir en Litres.
    return (this->longueur_ * this->largeur_ * this->profondeur_) / 1000;
}