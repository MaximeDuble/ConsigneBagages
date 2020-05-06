#ifndef VCONSIGNE_HPP
#define VCONSIGNE_HPP

#include "Ticket.hpp"
#include "vBagage.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

#include <set>

struct vCasier {

    // Numéro unique allant de 1 à la capacité de la consigne.
    int numero;

    // Pointeur vers le bagage contenu dans le casier, nullptr si aucun bagage.
    vBagage* bagage;

    // Volume du casier en litres.
    float volume;

    /** Cet attribut permet de savoir quel casier a été libéré il y a le plus longtemps. 
     *  En effet, plus indexLiberation sera proche de 0, plus le casier aura été libéré il y a longtemps (0 si jamais rempli).
     *  Nous pouvons ainsi ordonné notre liste ordonnée (set) de casiers en fonction de volumes et de l'indexLiberation. 
    */
    int indexLiberation;

    
    bool operator< (const vCasier& autreCasier) const {

        // Si les deux casiers ont un volume égal, alors celui qui a été libéré en dernier (qui a l'indexLiberation le plus faible) est prioritaire et donc avant l'autre dans le set.
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
        * @pre volumes.size() == nbCasiers.size(), taille des tableaux > 0 et toutes les valeurs de nbCasiers et de volumes sont > 0
        * @throw invalid_argument si nbCasiers.size() != volumes.size();
        * @throw invalid_argument si nbCasiers.size() == 0 || volumes.size() == 0
        * @throw invalid_argument si une des valeurs de nbCasiers ou volumes est <= 0.
        * 
        */
        vConsigne(std::vector<float> volumes, std::vector<int> nbCasiers);
        ~vConsigne();
        

        /** 
        * Détermine si la consigne est pleine. 
        * @return true si la consigne n'a aucune place disponible pour accueillir un nouveau bagage, false sinon.
        */
        bool estPleine() const;

        /** Détermine si un casier de taille suffisante est disponible pour accueillir un bagage de volume volume.
         * @param volume, le volume du bagage.
         * @pre volume > 0 (vérifié à la création du bagage).
         * @return true si un casier est trouvé.
         */
        bool casierDeBonneTailleDisponible(float volume) const;

        /** Depose le bagage du client dans un casier de taille optimale et retourne un ticket. 
        *  
        *  @param bagage, pointeur vers une instance d'un objet héritant de la classe vBagage
        *  @pre estPleine() = false et casierDeBonneTailleDisponible(volume->getVolume()) = true.
        *  @return Ticket, le ticket du casier ou est stocké le bagage.
        *  @throw length_error, si la consigne est pleine ou qu'aucun casier n'est disponible pour un bagage de ce volume.
        */
        Ticket deposerBagage(vBagage* bagage);


        /** Rends au client le bagage se situant de le casier associé au Ticket. 
         * @param ticket, le ticket du casier.
         * @return bagage du client.
         * @throw out_of_range, si aucun casier n'est associé à ce ticket.
        */
        vBagage* retirerBagage(Ticket ticket);

        void d_afficherCasiersLibres();

        


    private:

        // Nombre de casiers totaux.
        int capacite_;

        // Table de hachage associant un Ticket à son Casier.
        std::unordered_map<Ticket, vCasier> casiersPleins_;

        /** Nombre de casiers libérés depuis le début de l'existence de la consigne, permet de savoir quel casier a été libéré il y a le plus longtemps et donc quel casier choisir
         *  valeur maximale d'un unsigned long : 4 294 967 295.
        */
        long nbCasiersLiberes_;

        // Liste des casiers disponibles, ordonnés en fonction de leur volume et de leur date de dernière utilisation.
        std::set<vCasier> casiersDisponibles_;





};


#endif