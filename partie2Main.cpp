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

    /** 
     * TAPER "make mainPartie2" dans un terminal pour compiler cette partie.
    */

    srand(time(NULL));

    // 1 - Création d'une consigne de 14 casiers.

    std::vector<float> volumes = {1, 5.5, 10, 15};
    std::vector<int> nbDispo = {2, 2, 2, 2};

        // TODO : TRY

    vConsigne consigne(volumes, nbDispo);
    
    // 2 - Création de 6 bagages, 2 malettes, 2 cylindres, 2 demi-sphères.

    vBagage* malette1 = new vMalette("Malette1", "Marque", 2000.5, 10.8, 15.2);
    vBagage* malette2 = new vMalette("Malette2", "Marque", 21.2, 5.8, 18.7);

    vBagage* cylindre1 = new vCylindre("Cylindre1", "Marque", 28.4, 17.4);
    vBagage* cylindre2 = new vCylindre("Cylindre2", "Marque", 13.2, 17.4);
    
    vBagage* demisphere1 = new vDemiSphere("Demi-sphère1" ,"Marque", 34);
    vBagage* demisphere2 = new vDemiSphere("Demi-sphère2" ,"Marque", 36);


    // ESSAIS

    try {
        
        consigne.d_afficherCasiersLibres();

        Ticket t1 = consigne.deposerBagage(demisphere1);
        consigne.d_afficherCasiersLibres();

        Ticket t2 = consigne.deposerBagage(demisphere2);
        consigne.d_afficherCasiersLibres();

        consigne.retirerBagage(t1);
        consigne.d_afficherCasiersLibres();
            
        consigne.retirerBagage(t2);
        consigne.d_afficherCasiersLibres();

        Ticket t3 = consigne.deposerBagage(cylindre1);
        consigne.retirerBagage(t3);
        consigne.d_afficherCasiersLibres();

        // Dépot d'un bagage trop gros.
        Ticket t4 = consigne.deposerBagage(malette1);
        
    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    
    consigne.d_afficherCasiersLibres();


    return 0;
}