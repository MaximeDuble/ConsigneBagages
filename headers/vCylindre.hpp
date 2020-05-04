#ifndef VCYLINDRE_HPP
#define VCYLINDRE_HPP

#include "vBagage.hpp"
#include <string>

class vCylindre: public vBagage {

    public: 
        vCylindre(std::string nom, std::string marque, float diametre, float profondeur);
        
        // Utilisation des constructeurs de vBagage.
        using vBagage::vBagage;

    private:

        /** 
         * Retourne le volume en litres du bagage en forme de cylindre, en fonction de son diamètre et de sa profondeur donnés en centimètres.
        */
        float calculerVolume() const override;

        // Diamètre donné en centimètres du bagage en forme de cylindre.
        float diametre_;
        // Profondeur donnée en centimètres du bagage en forme de cylindre.
        float profondeur_;


};

#endif