#include "../headers/vBagage.hpp"

vBagage::vBagage(std::string nom, std::string marque) : nom_(nom), marque_(marque), volume_(0) {
}

vBagage::vBagage() : nom_("Aucun nom"), marque_("Aucune marque"), volume_(0) {

}

float vBagage::getVolume() const {
    return this->volume_;
}

std::string vBagage::getNom() const {
    return this->nom_;
}