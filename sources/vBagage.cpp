#include "../headers/vBagage.hpp"

vBagage::vBagage(float volume) : volume_(volume) {
    // assert volume 
}

float vBagage::getVolume() const {
    return this->volume_;
}