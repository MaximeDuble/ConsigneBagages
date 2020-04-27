#include "headers/Consigne.hpp"
#include "headers/Ticket.hpp"
#include <iostream>

int main() {

    // Permet l'initialisation unique de la fonction de randomisation.
    srand(time(NULL));

    Consigne consigne(15);

    consigne.d_afficherFile();

    Bagage bagageMaxime = "Bagage de test";

    Ticket ticketMaxime = consigne.deposerBagage(bagageMaxime);

    std::cout << "Ticket maxime : " << ticketMaxime.d_getCode() << std::endl;

    consigne.d_afficherFile();

    std::cout << consigne.retirerBagage(ticketMaxime) << std::endl;

    consigne.d_afficherFile();

    Consigne aconsigne(0);

    try {
        aconsigne.deposerBagage(Bagage("Test"));
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    

    return 0;
}