#include "../headers/vMalette.hpp"

vMalette::vMalette(float longueur, float largeur, float profondeur) : longueur_(longueur), largeur_(largeur), profondeur_(profondeur) {

    this->volume_ = this->calculerVolume();
}

float vMalette::calculerVolume() const {   
    return (this->longueur_ * this->largeur_ * this->profondeur_) / 1000;
}