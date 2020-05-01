#ifndef VMALETTE_HPP
#define VMALETTE_HPP

#include "vBagage.hpp"

class vMalette: public vBagage {

    public: 

        vMalette(float longueur, float largeur);
        float calculerVolume(float longueur, float largeur) const;

    private:


};

#endif