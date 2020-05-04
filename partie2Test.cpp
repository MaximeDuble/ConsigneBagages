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

    std::vector<float> volumes = {1, 5.5, 10, 15};
    std::vector<int> nbDispo = {2, 3, 0, 1};

    vBagage* malette = new vMalette("Malette", "Marque", 15.2, 10.8, 15.7);
    std::cout << malette->getVolume() << std::endl;

    vBagage* cylindre = new vCylindre("Cylindre", "Marque", 15.2, 17.4);
    std::cout << cylindre->getVolume() << std::endl;

    vBagage* demisphere = new vDemiSphere("Demi-sphère" ,"Marque", 15.2);
    std::cout << demisphere->getVolume() << std::endl;


    try {
        vConsigne consigne(volumes, nbDispo);
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(0.5) << std::endl;
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(4) << std::endl;
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(6) << std::endl;
        consigne.d_afficherCasiersLibres();
        //consigne.deposerBagage(malette.get());

    } catch (const char* s) {
        std::cerr << s << std::endl;
    }




}