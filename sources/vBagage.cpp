#include "../headers/vBagage.hpp"

vBagage::vBagage(float volume) {
    this->volume_ = volume;
}

float vBagage::getVolume() const {
    return this->volume_;
}