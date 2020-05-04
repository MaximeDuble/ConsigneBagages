#ifndef VBAGAGE_HPP
#define VBAGAGE_HPP
#include <string>

class vBagage {

    public:

        vBagage();
        vBagage(std::string nom, std::string marque);
        
        /**
         * Retourne le volume en litres d'un bagage. 
         */
        float getVolume() const;

    protected:

        /** 
         * Calcule le volume en litres du bagage, en fonction de ses différentes dimensions. Fonction virtuelle pure.
        */
        virtual float calculerVolume() const = 0;

        // Volume en litres du bagage.
        float volume_;
        std::string nom_;
        std::string marque_;

};

#endif