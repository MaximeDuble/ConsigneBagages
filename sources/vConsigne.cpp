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

    for(int i = 0 ; i < volumes.size() ; i++) {

        if(volumes[i] < 0 || nbCasiers[i] < 0) {
            throw "ERREUR : Valeur inférieure à 0 impossible !";
        }

        this->capacite_ += nbCasiers[i];

        this->nbCasiersDisponiblesParVolumes_.push_back(std::make_pair(volumes[i], nbCasiers[i]));

        // INSERTION MAP CASIERS DISPOS

        this->casiersLibres_.insert({volumes[i], this->genererFileVide(volumes[i], indexDebutCasier, indexDebutCasier + nbCasiers[i] - 1)});

        indexDebutCasier += nbCasiers[i];

    }

    // Au debut, tous les casiers sont disponibles.
    this->nbCasiersDisponibles_ = this->capacite_;

    this->d_afficherVecteur();

    // Utilisation de la fonction standard "sort" (de complexité temporelle moyenne nlog(n)) afin de trier notre vecteur de pair en fonction de la première valeur.
    // Peut être utilisation de tri par insertion ? Tri rapide pas vraiment rapide pour un petit tableau.
    std::sort(this->nbCasiersDisponiblesParVolumes_.begin(), this->nbCasiersDisponiblesParVolumes_.end());

    this->d_afficherVecteur();



}

vConsigne::~vConsigne() {

}

std::queue<vCasier> vConsigne::genererFileVide(float volume, int indexInitial, int nbCasiers) {
    std::queue<vCasier> fileCasiers;

    for (int i = indexInitial ; i <= nbCasiers ; i++) {
        fileCasiers.push(vCasier{i, nullptr, volume});
    }

    return fileCasiers;


} 

bool vConsigne::estPleine() const {

    return this->nbCasiersDisponibles_ == 0; 

}

Ticket vConsigne::deposerBagage(vBagage* bagage) {

    if(this->estPleine()) throw "ERREUR : La consigne est pleine.";

    float volumeCasier = 0;

    // A TESTER
    try {
        volumeCasier = this->trouverVolumeCasierDisponibleOptimal(bagage->getVolume());
    } catch (const char* s) {
        throw s;
    }

    Ticket ticketClient;

    // Deplacer casier dans l'autre unordered map
    vCasier casierChoisi = this->casiersLibres_.find(volumeCasier)->second.front();
    this->casiersLibres_.find(volumeCasier)->second.pop();

    casierChoisi.bagage = bagage;
    this->casiersPleins_.insert({ticketClient, casierChoisi});


    // Abaisser le nombre de places dispos dans la variable globale et dans le tableau

    --this->nbCasiersDisponibles_;

    return ticketClient;
}

vBagage* vConsigne::retirerBagage(Ticket ticket) {

}

// PRIVATE

float vConsigne::trouverVolumeCasierDisponibleOptimal(float volumeBagage) {

    float volumeOptimalCasierDispo;

    // Passe à true quand un casier à été trouvé
    bool flagVolumeTrouve = false;

    auto it = this->nbCasiersDisponiblesParVolumes_.begin();

    while(!flagVolumeTrouve && it != nbCasiersDisponiblesParVolumes_.end()) {

        // paire.first est un volume de caiser et paire.second le nombre de casiers disponibles à ce volume.
        if(it->first >= volumeBagage && it->second > 0) {
            flagVolumeTrouve = true;
            volumeOptimalCasierDispo = it->first;

            // Un casier a été trouvé, on diminue le nombre de casiers disponibles pour ce volume.
            it->second--;
        }

        ++it;

    }

    if (!flagVolumeTrouve) throw "ERREUR : Aucun casier de la taille demandée n'est disponible !";

    return volumeOptimalCasierDispo;

}

// DEBOGAGE

void vConsigne::d_afficherVecteur() const {

    for (auto paire : nbCasiersDisponiblesParVolumes_) {
        std::cout << paire.first << " : " << paire.second << std::endl;
    }
}

void vConsigne::d_afficherCasiersLibres() const {

    std::unordered_map<float, std::queue<vCasier>> copy = this->casiersLibres_;

    for (auto const& pair : copy) {
        std::cout << "{" << pair.first << ":" << std::endl;
        d_afficherFile(pair.second);
        std::cout << "}" << std::endl;
    }
}

void vConsigne::d_afficherFile(std::queue<vCasier> file) const {

    std::queue<vCasier> fileCopie = file;

    while (!fileCopie.empty()) {

        std::cout << "Casier numéro : " << fileCopie.front().numero << " (" << fileCopie.front().volume << ") " << "; Bagage : " << fileCopie.front().bagage << std::endl;
        fileCopie.pop();
    }

}