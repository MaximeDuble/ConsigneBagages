#include "headers/Consigne.hpp"
#include "headers/Ticket.hpp"
#include <iostream>
#include <string>

std::string conversionBoolString(bool b) {
    return (b ? "vrai" : "faux");
}

int main() {

    /** 
     * TAPER "make mainPartie1" dans un terminal pour compiler cette partie.
    */

    // Permet l'initialisation unique de la fonction de randomisation.
    srand(time(NULL));

    // Manipulation classique d'une consigne.

    try {
        // Création d'une consigne de 3 casiers.
        Consigne consigne(3);

        std::cout << "La consigne est-elle pleine : "<< conversionBoolString(consigne.estPleine()) << std::endl;

        // File après la création.
        consigne.d_afficherFile();

        Bagage bagageTest1 = "Bagage de test 1";
        Bagage bagageTest2 = "Bagage de test 2";

        Ticket ticket1 = consigne.deposerBagage(bagageTest1);

        // bagageTest1 est bien dans le casier 1
        consigne.d_afficherFile();

        Ticket ticket2 = consigne.deposerBagage(bagageTest2);

        // bagageTest2 est bien dans le casier 2.
        consigne.d_afficherFile();

        // L'affichage est bien "Bagage de test 2"
        std::cout << consigne.retirerBagage(ticket2) << std::endl;
        // Le casier 2 est bien retourné à la fin de la file.
        consigne.d_afficherFile();

        // L'affichage est bien "Bagage de test 1"
        std::cout << consigne.retirerBagage(ticket1) << std::endl;
        // Le casier 1, malgré qu'il ait été rempli avant le 2 est repassé derrière le 2 car a été libéré après.
        consigne.d_afficherFile();

    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Création d'une consigne vide.

    try {
        // Création d'une consigne de 0 casiers, erreur car la taille doit être supérieur à 0.
        Consigne consigne(0);

    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Dépot d'un bagage alors que la consigne est pleine.

    try {
        // Création d'une consigne de 1 casiers.
        Consigne consigne(1);

        consigne.d_afficherFile();

        Bagage bagageDeTest1 = "Bagage de test 1";
        Bagage bagageDeTest2 = "Bagage de test 2";

        Ticket ticket1 = consigne.deposerBagage(bagageDeTest1);

        std::cout << "La consigne est-elle pleine : " << conversionBoolString(consigne.estPleine()) << std::endl;

        // Déposer un bagage alors que la consigne est pleine
        Ticket ticket2 = consigne.deposerBagage(bagageDeTest2);


    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Retrait d'un bagage avec un ticket non créé par la consigne.

    try {
        Consigne consigne(1);
        
        Bagage bagageDeTest1 = "Bagage de test 1";

        Ticket ticket1 = consigne.deposerBagage(bagageDeTest1);

        Ticket ticket2; 

        // Retrait d'un bagage avec un ticket n'appartenant à aucun bagage.
        Bagage bagageTrouve = consigne.retirerBagage(ticket2);
    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    

    return 0;
}