#ifndef VMALETTE_HPP
#define VMALETTE_HPP

#include "vBagage.hpp"
#include <string>

class vMalette: public vBagage {

    public: 
        vMalette(std::string nom, std::string marque, float longueur, float largeur, float profondeur);
        
        // Utilisation des constructeurs de vBagage.
        using vBagage::vBagage;

    private:

        /** 
         * Retourne le volume en litres du bagage en forme de rectangle (pavé), en fonction de sa longueur, sa largeur, et sa profondeur donnés en centimètres.
        */
        float calculerVolume() const override;

        // Longueur en centimètres.
        float longueur_;
        // Largeur en centimètres.
        float largeur_;
        // Profondeur en centimètres.
        float profondeur_;


};

#endif