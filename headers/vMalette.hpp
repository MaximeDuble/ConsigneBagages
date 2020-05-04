#ifndef VMALETTE_HPP
#define VMALETTE_HPP

#include "vBagage.hpp"

class vMalette: public vBagage {

    public: 

        vMalette(float longueur, float largeur, float profondeur);
        float calculerVolume() const override;

    private:

        float longueur_;
        float largeur_;
        float profondeur_;


};

#endif