#include "../headers/vConsigne.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

vConsigne::vConsigne() {

    // TODO : Methode ou le mec tape directement les casiers disponibles etc.

}

/** Initialise une consigne avec nbCasiers[i] d'un volume volumes[i] disponibles avec i de 0 à nbCasiers.size()
 * 
 *  @param volumes, un vecteur de nombres flottants correspondant aux différents volumes disponibles
 *  @param nbCasiers, un vecteur d'entiers correspondant aux nbCasiers disponibles associés aux différents volumes disponibles.
 *  @throw Erreur si les tableaux en entrée ont une taille différent ou si l'une de leur valeur est strictement inférieure à 0.
 * 
*/
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
/**
 * Génère une file de "nbCasiers" casiers d'un volume "volume" avec des numéros allant de "indexInitial" à "indexInitial" + "nbCasiers".
 * @param volume, le volume de chaque casier contenu dans la file.
 * @param indexInitial, l'index dans la consigne du premier casier de la file.
 * @param nbCasiers, le nombre de casiers créés.
 * @return fileCasiers, la file remplie de casiers.
 */
std::queue<vCasier> vConsigne::genererFileVide(float volume, int indexInitial, int nbCasiers) {
    std::queue<vCasier> fileCasiers;

    for (int i = indexInitial ; i <= nbCasiers ; i++) {
        fileCasiers.push(vCasier{i, nullptr, volume});
    }

    return fileCasiers;


} 


/** 
 * Détermine si la consigne est pleine. 
 * @return true si la consigne n'a aucune place disponible pour accueillir un nouveau bagage, false sinon.
*/
bool vConsigne::estPleine() {

    return this->nbCasiersDisponibles_ == 0; 

}

/** Depose le bagage du client dans un casier de taille optimale et retourne un ticket. 
 *  
 *  @param bagage, pointeur vers une instance d'un objet héritant de la classe vBagage
 *  @return Ticket, le ticket du casier ou est stocké le bagage.
 *  @throw erreur si la consigne est pleine ou qu'aucun casier n'est disponible pour un bagage de ce volume.
*/
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

/** Rends au client le bagage se situant de le casier associé au Ticket. 
 * @param ticket, le ticket du casier.
 * @return bagage du client.
*/
vBagage* vConsigne::retirerBagage(Ticket ticket) {

}

// PRIVATE

/** Retourne le volume optimal d'un casier disponible pour acceuillir un bagage de volume volumeBagage. 
 * @param volumeBagage, le volume du bagage que l'on veut placer dans la consigne.
 * @return le volume d'un casier optimal disponible.
 * @throw erreur si aucun casier de la taille demandée n'est disponible.
*/
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
            it->second--;
        }

        ++it;

    }

    if (!flagVolumeTrouve) throw "ERREUR : Aucun casier de la taille demandée n'est disponible !";

    return volumeOptimalCasierDispo;

}

// DEBOGAGE

void vConsigne::d_afficherVecteur() {

    for (auto paire : nbCasiersDisponiblesParVolumes_) {
        std::cout << paire.first << " : " << paire.second << std::endl;
    }
}

void vConsigne::d_afficherCasiersLibres() {

    std::unordered_map<float, std::queue<vCasier>> copy = this->casiersLibres_;

    for (auto const& pair : copy) {
        std::cout << "{" << pair.first << ":" << std::endl;
        d_afficherFile(pair.second);
        std::cout << "}" << std::endl;
    }
}

void vConsigne::d_afficherFile(std::queue<vCasier> file) {

    std::queue<vCasier> fileCopie = file;

    while (!fileCopie.empty()) {

        std::cout << "Casier numéro : " << fileCopie.front().numero << " (" << fileCopie.front().volume << ") " << "; Bagage : " << fileCopie.front().bagage << std::endl;
        fileCopie.pop();
    }

}