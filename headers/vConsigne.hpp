#ifndef VCONSIGNE_HPP
#define VCONSIGNE_HPP

#include "Ticket.hpp"
#include "vBagage.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

#include <set>

struct vCasier {

    int numero;
    vBagage* bagage;
    float volume;
    int indexLiberation;

    bool operator< (const vCasier& autreCasier) const {

        if(this->volume == autreCasier.volume) {
            return this->indexLiberation <= autreCasier.indexLiberation;
        } else {
            return this->volume < autreCasier.volume;
        }
    }

    bool operator==(const vCasier& autreCasier) const {
        // Chaque casier a un numéro unique, il est inutile de comparer les autres attributs.
        return this->numero == autreCasier.numero;
    }

};

class vConsigne {

    public: 

        vConsigne();

        /** Initialise une consigne avec nbCasiers[i] d'un volume volumes[i] disponibles avec i de 0 à nbCasiers.size()
        * @param volumes, un vecteur de nombres flottants correspondant aux différents volumes disponibles
        * @param nbCasiers, un vecteur d'entiers correspondant aux nbCasiers disponibles associés aux différents volumes disponibles.
        * @throw Erreur si les tableaux en entrée ont une taille différent ou si l'une de leur valeur est strictement inférieure à 0.
        */
        vConsigne(std::vector<float>, std::vector<int>);
        ~vConsigne();
        

        /** 
        * Détermine si la consigne est pleine. 
        * @return true si la consigne n'a aucune place disponible pour accueillir un nouveau bagage, false sinon.
        */
        bool estPleine() const;

        /** Depose le bagage du client dans un casier de taille optimale et retourne un ticket. 
        *  
        *  @param bagage, pointeur vers une instance d'un objet héritant de la classe vBagage
        *  @return Ticket, le ticket du casier ou est stocké le bagage.
        *  @throw erreur si la consigne est pleine ou qu'aucun casier n'est disponible pour un bagage de ce volume.
        */
        Ticket deposerBagage(vBagage* bagage);

        /** Rends au client le bagage se situant de le casier associé au Ticket. 
         * @param ticket, le ticket du casier.
         * @return bagage du client.
        */
        vBagage* retirerBagage(Ticket ticket);

        

        

    // DEBOGAGE

        void d_afficherVecteur() const;
        void d_afficherCasiersLibres() const;
        void d_afficherFile(std::queue<vCasier> file) const;

    private:

        /** Retourne le volume optimal d'un casier disponible pour acceuillir un bagage de volume volumeBagage. 
        * @param volumeBagage, le volume du bagage que l'on veut placer dans la consigne.
        * @return le volume d'un casier optimal disponible.
        * @throw erreur si aucun casier de la taille demandée n'est disponible.
        */
        float trouverVolumeCasierDisponibleOptimal(float volumeBagage);


        /**
         * Génère une file de "nbCasiers" casiers d'un volume "volume" avec des numéros allant de "indexInitial" à "indexInitial" + "nbCasiers".
         * @param volume, le volume de chaque casier contenu dans la file.
         * @param indexInitial, l'index dans la consigne du premier casier de la file.
         * @param nbCasiers, le nombre de casiers créés.
         * @return fileCasiers, la file remplie de casiers.
         */
        std::queue<vCasier> genererFileVide(float volume, int indexInitial, int nbCasiers);

        // Nombre de casiers totaux.
        int capacite_;
        // Nombre de casiers libres.
        int nbCasiersDisponibles_;

        // Table de hachage associant un Ticket à son Casier.
        std::unordered_map<Ticket, vCasier> casiersPleins_;
        // Table de hachage associant une file de casiers libres de même volume à leur volume.
        std::unordered_map<float, std::queue<vCasier>> casiersLibres_;
        // Tableau de paire de volumes associés au nombre de casiers disponibles de ce volume.
        std::vector<std::pair<float, int>> nbCasiersDisponiblesParVolumes_;

        std::set<vCasier> casiersDisponbibles_;

        int nbCasiersLiberes_;





};


#endif