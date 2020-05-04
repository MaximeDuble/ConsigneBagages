#include "headers/vConsigne.hpp"
#include "headers/Ticket.hpp"
#include "headers/vBagage.hpp"
#include "headers/vMalette.hpp"
#include "headers/vCylindre.hpp"
#include "headers/vDemiSphere.hpp"

#include <iostream>
#include <vector>
#include <memory>

int main() {

    srand(time(NULL));

    // 1 - Création d'une consigne de 14 casiers.

    std::vector<float> volumes = {1, 5.5, 10, 15};
    std::vector<int> nbDispo = {2, 2, 2, 2};

        // TODO : TRY

    vConsigne consigne(volumes, nbDispo);
    
    // 2 - Création de 15 bagages, 5 malettes, 5 cylindres, 5 demi-sphères.

    vBagage* malette1 = new vMalette("Malette1", "Marque", 2000.5, 10.8, 15.2);
    vBagage* malette2 = new vMalette("Malette2", "Marque", 21.2, 5.8, 18.7);
    vBagage* malette3 = new vMalette("Malette3", "Marque", 12.2, 10.8, 14.7);
    vBagage* malette4 = new vMalette("Malette4", "Marque", 15.2, 10.8, 12.7);
    vBagage* malette5 = new vMalette("Malette5", "Marque", 18.2, 14.8, 25.7);

    vBagage* cylindre1 = new vCylindre("Cylindre1", "Marque", 14.2, 17.4);
    vBagage* cylindre2 = new vCylindre("Cylindre2", "Marque", 13.2, 17.4);
    vBagage* cylindre3 = new vCylindre("Cylindre3", "Marque", 12.2, 17.4);
    vBagage* cylindre4 = new vCylindre("Cylindre4", "Marque", 11.2, 17.4);
    vBagage* cylindre5 = new vCylindre("Cylindre5", "Marque", 10.2, 17.4);
    
    vBagage* demisphere1 = new vDemiSphere("Demi-sphère1" ,"Marque", 34);
    vBagage* demisphere2 = new vDemiSphere("Demi-sphère2" ,"Marque", 36);
    vBagage* demisphere3 = new vDemiSphere("Demi-sphère3" ,"Marque", 35);
    vBagage* demisphere4 = new vDemiSphere("Demi-sphère4" ,"Marque", 26);
    vBagage* demisphere5 = new vDemiSphere("Demi-sphère5" ,"Marque", 37);

    // ESSAIS

    try {
        
        consigne.d_afficherCasiersLibres();

        Ticket t1 = consigne.deposerBagage(demisphere1);
                consigne.d_afficherCasiersLibres();

        Ticket t2 = consigne.deposerBagage(demisphere2);
                consigne.d_afficherCasiersLibres();

        consigne.retirerBagage(t2);
                consigne.d_afficherCasiersLibres();

        Ticket t3 = consigne.deposerBagage(demisphere3);


        
        
    } catch (char const* s) {
        std::cerr << s << std::endl;
    }
    

    std::cout << " " << std::endl;
    consigne.d_afficherCasiersLibres();


    return 0;
}