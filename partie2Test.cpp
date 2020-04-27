#include "headers/vConsigne.hpp"
#include "headers/Ticket.hpp"
#include "headers/vBagage.hpp"
#include <iostream>
#include <vector>

int main() {

    srand(time(NULL));

    std::vector<float> volumes = {1, 5.5, 10, 15};
    std::vector<int> nbDispo = {2, 3, 0, 1};

    try {
        vConsigne consigne(volumes, nbDispo);
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(0.5) << std::endl;
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(4) << std::endl;
        std::cout << consigne.trouverVolumeCasierDisponibleOptimal(6) << std::endl;
        consigne.d_afficherCasiersLibres();

    } catch (const char* s) {
        std::cerr << s << std::endl;
    }




}