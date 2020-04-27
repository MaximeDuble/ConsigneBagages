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

        Consigne(int size);
        ~Consigne();
        bool estPleine();
        Ticket deposerBagage(Bagage bagage);
        Bagage retirerBagage(Ticket ticket);

        // DEBOGAGE

        size_t d_tailleActuelle();
        void d_afficherFile();

    private:

        // Table de hashage ayant pour clé le Ticket et pour valeur un Bagage.
        std::unordered_map<Ticket, Casier> casiersPleins_;

        // Nombre max de bagages que la consigne peut accueillir.
        int capacite_;

        // File d'attente de casiers libres en fonction de leur date de dernier usage (FIFO)
        std::queue<Casier> casiersLibres_;


};

#endif