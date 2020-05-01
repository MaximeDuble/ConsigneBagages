#ifndef TICKET_HPP
#define TICKET_HPP
#include <cstdlib>
#include <string>

// TODO : AJOUTER COMMENTAIRES //

class Ticket {
    public :

        Ticket();
        ~Ticket();
        size_t hash_code() const;
        bool operator==(Ticket const& autre) const;
        bool operator!=(Ticket const& autre) const;

        // DEBOGAGE

        std::string d_getCode() const;

    private:
        std::string code_;

};

namespace std {
    template <> struct hash<Ticket> {
        size_t operator() (const Ticket& t) const {
            return t.hash_code();
        }
    };
}

#endif