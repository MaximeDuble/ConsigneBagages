#ifndef VDEMISPHERE_HPP
#define VDEMISPHERE_HPP

#include "vBagage.hpp"
#include <string>

class vDemiSphere: public vBagage {

    public: 
        vDemiSphere(std::string nom, std::string marque, float diametre);

        // Utilisation des constructeurs de vBagage.
        using vBagage::vBagage;

    private:

        /** 
         * Retourne le volume en litres du bagage en fonction de son diamètre donné en centimètres.
        */
        float calculerVolume() const override;

        // Diamètre en centimètres du bagage en forme de demi-sphère.
        float diametre_;


};

#endif