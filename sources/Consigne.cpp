#include "../headers/Consigne.hpp"
#include <iostream>
#include <string>
#include <queue>

Consigne::Consigne(int capacite) : capacite_(capacite) {
 
    for (int i = 0 ; i < capacite ; i++) {
        this->casiersLibres_.push(Casier{i+1, ""});
    }
}

Consigne::~Consigne() {
    
}

bool Consigne::estPleine() const {
    return this->casiersLibres_.empty();
}

Ticket Consigne::deposerBagage(Bagage bagage) {



    if (this->estPleine()) throw "ERREUR : La consigne est pleine.";
    
    // Récupère le ticket associé au casier le moins récemment utilisé.
    Ticket ticketClient;
    Casier casierUtilise = this->casiersLibres_.front();

    casierUtilise.bagage = bagage;
    // Rajoute le ticket du casier et son bagage dans un table de hashage.
    this->casiersPleins_.insert({ticketClient, casierUtilise});
    // Retirer le ticket du casier désormais utilisé de la file des casiers libres. 
    this->casiersLibres_.pop();

    // Donne au client le ticket associé au casier dans lequel son bagage est.
    return ticketClient;

}

Bagage Consigne::retirerBagage(Ticket ticket){

    auto iterateur = this->casiersPleins_.find(ticket);

    if (iterateur != this->casiersPleins_.end()) { // Bagage trouvé.

        // Recupère le bagage du client.
        Bagage bagageTrouve = iterateur->second.bagage; 

        iterateur->second.bagage = ""; // On remets le bagage à 0

        // Rajoute le casier à la fin de la liste des casiers libres.
        this->casiersLibres_.push(iterateur->second);

        // Enlève le ticket et son casier associé de la table de hashage.
        this->casiersPleins_.erase(iterateur);

        
        

        return bagageTrouve;
    } else {
        
        throw std::string("Bagage non trouvé.");
    }
}

// DEBOGAGE

size_t Consigne::d_tailleActuelle() const {
    return this->casiersPleins_.size();
}

void Consigne::d_afficherFile() const {

    std::queue<Casier> fileCopie = this->casiersLibres_;

    std::cout << "" << std::endl;

    while (!fileCopie.empty()) {

        std::cout << "Casier numéro : " << fileCopie.front().numero << ". Bagage : " << fileCopie.front().bagage << std::endl;
        fileCopie.pop();
    }
}