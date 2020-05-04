#include "../headers/vConsigne.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

vConsigne::vConsigne() {

    // TODO : Methode ou le mec tape directement les casiers disponibles etc.

}

vConsigne::vConsigne(std::vector<float> volumes, std::vector<int> nbCasiers) {

    if(volumes.size() != nbCasiers.size()) {
        throw "ERREUR : Tableaux de tailles différentes";
    }

    int indexDebutCasier = 1;

    for(int i = 0 ; i < nbCasiers.size() ; i++) {

        if(volumes[i] < 0 || nbCasiers[i] < 0) {
            throw "ERREUR : Valeur inférieure à 0 impossible !";
        }


        for (int indexCasier = indexDebutCasier ; indexCasier < indexDebutCasier + nbCasiers[i] ; indexCasier++) {

            this->casiersDisponibles_.insert({indexCasier, nullptr, volumes[i], 0});
        }

        indexDebutCasier += nbCasiers[i];


        this->capacite_ += nbCasiers[i];

    }

    // Au début, tous les casiers sont disponibles.
    this->nbCasiersDisponibles_ = this->capacite_;

    // Au début, aucun casier n'a été libéré.
    this->nbCasiersLiberes_ = 0;
}

vConsigne::~vConsigne() {

}

bool vConsigne::estPleine() const {

    return this->nbCasiersDisponibles_ == 0; 

}

Ticket vConsigne::deposerBagage(vBagage* bagage) {

    if(this->estPleine()) throw "ERREUR : La consigne est pleine.";

    Ticket ticketClient;
    

    auto it = this->casiersDisponibles_.lower_bound({0, nullptr, bagage->getVolume(), 0});

    if (it == this->casiersDisponibles_.end()) throw "ERREUR : Aucun casier de taille suffisante disponible.";

    vCasier casierChoisi = *it;

    this->casiersDisponibles_.erase(it);
    
    casierChoisi.bagage = bagage;
    this->casiersPleins_.insert({ticketClient, casierChoisi});

    --this->nbCasiersDisponibles_;

    return ticketClient;
}

vBagage* vConsigne::retirerBagage(Ticket ticket) {
    

    auto it = this->casiersPleins_.find(ticket);

    if (it != this->casiersPleins_.end()) {

        this->nbCasiersLiberes_++;  
        vBagage* bagageTrouve = it->second.bagage;

        it->second.indexLiberation = this->nbCasiersLiberes_;

        it->second.bagage = nullptr;

        this->casiersDisponibles_.insert(it->second);
        this->casiersPleins_.erase(it);

        

        this->nbCasiersDisponibles_++;

        return bagageTrouve;
   
    } else throw std::string("Bagage non trouvé.");

      
}

// DEBOGAGE

void vConsigne::d_afficherCasiersLibres() {

    std::cout << "" << std::endl;
    for(const auto& e : this->casiersDisponibles_) {
        std::cout << e.numero << " : " << e.volume << " : " << e.indexLiberation << std::endl;
    }
}
