#include "headers/Consigne.hpp"
#include "headers/Ticket.hpp"
#include <iostream>

int main() {

    /** 
     * TAPER "make main1" dans un terminal pour compiler cette partie.
    */

    // Permet l'initialisation unique de la fonction de randomisation.
    srand(time(NULL));

    try {
        // Création d'une consigne de 15 casiers.
        Consigne consigne(15);

        consigne.d_afficherFile();

        Bagage bagageMaxime = "Bagage de test";

        Ticket ticketMaxime = consigne.deposerBagage(bagageMaxime);

        consigne.d_afficherFile();

        // L'affichage est bien "Bagage de test"
        std::cout << consigne.retirerBagage(ticketMaxime) << std::endl;

        // Le casier 1 est bien retourné à la fin de la file.
        consigne.d_afficherFile();
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    

    try {
        // Création d'une consigne de 0 casiers.
        Consigne aconsigne(0);
        // Depot d'un bagage dans une consigne sans place disponible -> erreur.
        aconsigne.deposerBagage(Bagage("Test"));
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    

    return 0;
}