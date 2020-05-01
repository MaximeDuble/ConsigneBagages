#include "../headers/vMalette.hpp"

vMalette::vMalette(float longueur, float largeur) {

    this->volume_ = this->calculerVolume(longueur, largeur);
}

float vMalette::calculerVolume(float longueur, float largeur) const {
    return longueur * largeur;
}