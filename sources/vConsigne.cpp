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

    // Index du premier casier d'une liste de casiers d'un même volume.
    int indexDebutCasier = 1;

    this->capacite_ = 0;

    // Création des casiers.
    for(int i = 0 ; i < nbCasiers.size() ; i++) {

        // Un volume ou un nombre de casiers ne doit pas être négatif.
        if(volumes[i] < 0 || nbCasiers[i] < 0) {
            throw "ERREUR : Valeur inférieure à 0 impossible !";
        }

        // Créé nbCasiers[i] vCasier, d'un volume volumes[i], avec des index débutant à indexDebutCasier (index du premier casier de ce volume).
        for (int indexCasier = indexDebutCasier ; indexCasier < indexDebutCasier + nbCasiers[i] ; indexCasier++) {

            this->casiersDisponibles_.insert({indexCasier, nullptr, volumes[i], 0});
        }

        // L'index de début de la prochaine liste de casiers évolue.
        indexDebutCasier += nbCasiers[i];

        this->capacite_ += nbCasiers[i];

    }

    // Au début, aucun casier n'a été libéré.
    this->nbCasiersLiberes_ = 0;

    std::cout << "La consigne s'est correctement initialisée, avec " << this->capacite_ << " nouveaux casiers !" << std::endl;
}

vConsigne::~vConsigne() {

}

bool vConsigne::estPleine() const {

    // Si aucun casier n'est disponible, alors la consigne est pleine.
    return this->casiersDisponibles_.size() == 0;

}

bool vConsigne::casierDeBonneTailleDisponible(float volume) const {

    auto it = this->casiersDisponibles_.lower_bound({0, nullptr, volume, 0});
    return (it != this->casiersDisponibles_.end());
}

Ticket vConsigne::deposerBagage(vBagage* bagage) {

    // On ne peut pas déposer de bagage si la consigne est pleine.
    if(this->estPleine() || !casierDeBonneTailleDisponible(bagage->getVolume())) throw "ERREUR : Aucun casier de taille suffisante disponible.";

    // Generation d'un nouveau ticket pour le client.
    Ticket ticketClient;

    // Deuxieme appel de la methode lower_bound qui aurait pu etre condensés mais il est demandé explicitement la présence de la méthode "casierDeBonneTailleDisponible".
    auto it = this->casiersDisponibles_.lower_bound({0, nullptr, bagage->getVolume(), 0});

    // Le casier optimal pour accueillir le bagage est pointé par it.
    vCasier casierChoisi = *it;

    // Suppression du casier de la liste des casiers disponibles.
    this->casiersDisponibles_.erase(it);
    
    // Insertion de la paire ticket / casier contenant le bagage dans la table de hachage.
    casierChoisi.bagage = bagage;
    this->casiersPleins_.insert({ticketClient, casierChoisi});

    return ticketClient;
}

vBagage* vConsigne::retirerBagage(Ticket ticket) {
    

    // On trouve l'itérateur pointant vers le casier associé au ticket passé en paramètre.
    auto it = this->casiersPleins_.find(ticket);

    // Si la condition n'est pas respectée, alors le bagage n'a pas été trouvé.
    if (it != this->casiersPleins_.end()) {

        //this->nbCasiersLiberes_++;  
        vBagage* bagageTrouve = it->second.bagage;

        // Changement de l'attribut "indexLiberation" du casier désormais libéré.
        it->second.indexLiberation = ++this->nbCasiersLiberes_;

        it->second.bagage = nullptr;

        // Le casier redevient de nouveau disponible.
        this->casiersDisponibles_.insert(it->second);
        // On supprime la paire ticket / vCasier de la table de hashage casiersPleins_.
        this->casiersPleins_.erase(it);

        return bagageTrouve;
   
    } else throw std::string("Bagage non trouvé.");

      
}

// DEBOGAGE

void vConsigne::d_afficherCasiersLibres() {

    std::cout << "" << std::endl;
    for(const auto& e : this->casiersDisponibles_) {
        std::cout << "Casier numéro : " << e.numero << ", de volume : " << e.volume << ", et d'index libération : " << e.indexLiberation << std::endl;
    }
}
