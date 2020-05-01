#ifndef VCONSIGNE_HPP
#define VCONSIGNE_HPP

#include "Ticket.hpp"
#include "vBagage.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

struct vCasier {

    int numero;
    vBagage* bagage;
    float volume;

};

class vConsigne {

    public: 

        vConsigne();
        vConsigne(std::vector<float>, std::vector<int>);
        ~vConsigne();
        
        bool estPleine() const;
        Ticket deposerBagage(vBagage* bagage);
        vBagage* retirerBagage(Ticket ticket);

        std::queue<vCasier> genererFileVide(float volume, int indexInitial, int nbCasiers);
        float trouverVolumeCasierDisponibleOptimal(float volumeBagage);

    // DEBOGAGE

        void d_afficherVecteur() const;
        void d_afficherCasiersLibres() const;
        void d_afficherFile(std::queue<vCasier> file) const;

    private:

        

        int capacite_;
        int nbCasiersDisponibles_;

        std::unordered_map<Ticket, vCasier> casiersPleins_;

        std::unordered_map<float, std::queue<vCasier>> casiersLibres_;
        std::vector<std::pair<float, int>> nbCasiersDisponiblesParVolumes_;





};


#endif