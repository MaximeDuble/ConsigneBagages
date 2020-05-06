#ifndef CONSIGNE_HPP
#define CONSIGNE_HPP
#include "Ticket.hpp"
#include <string>
#include <unordered_map>
#include <queue>

typedef std::string Bagage;

struct Casier {
  int numero; // Réellement utile que pour le gérant de la consigne.
  Bagage bagage;
};

class Consigne {

    public:

        /** 
         * Construit une consigne avec un nombre "size" de casiers.
         * @param "size", le nombre de casiers de la consigne.
         * @pre size > 0
         * @throw invalid_argument si size < 1.
        */
        Consigne(int size);
        ~Consigne();

        /** 
         * Retourne vrai si la consigne est pleine.
        */
        bool estPleine() const;

        /** 
         * Dépose un bagage dans une casier et rend le ticket pour le client.
         * @param "bagage", le bagage du client.
         * @pre estPleine() = false.
         * @return Ticket, le ticket du client associé au casier dans lequel est déposé le bagage.
         * @throw length_error, si estPleine() = ture.
        */
        Ticket deposerBagage(Bagage bagage);

        /** 
         * Rend le bagage disposé dans le casier associé au Ticket passé en paramètre.
         * @param "ticket", le ticket associé au casier ou est déposé le bagage.
         * @return Bagage, le bagage déposé dans le casier associé au Ticket ticket.
         * @throw out_of_range, aucun casier n'est associé à ce ticket.
        */
        Bagage retirerBagage(Ticket ticket);

        // DEBOGAGE

        size_t d_tailleActuelle() const;
        void d_afficherFile() const;

    private:

        // Table de hashage ayant pour clé le Ticket et pour valeur un Bagage.
        std::unordered_map<Ticket, Casier> casiersPleins_;

        // Nombre max de bagages que la consigne peut accueillir.
        int capacite_;

        // File d'attente de casiers libres en fonction de leur date de dernier usage (FIFO)
        std::queue<Casier> casiersLibres_;


};

#endif