#include "../headers/Ticket.hpp"
#include <string>
#include <cstdlib>

const int LONGUEUR_CHAINE = 50;


Ticket::Ticket() {

    std::string caracteresPossibles = "abcdefghijklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int tailleCaracteresPossibles = caracteresPossibles.size(); 
    this->code_ = "";

    for (int i = 0 ;  i < LONGUEUR_CHAINE ; i++) {
        this->code_ = this->code_ + caracteresPossibles[rand() % tailleCaracteresPossibles];
    }

}

Ticket::~Ticket() {

}

size_t Ticket::hash_code() const {

   std::hash<std::string> h;
   return h(this->code_);

}

bool Ticket::operator==(Ticket const& autre) const {
    return autre.code_ == this->code_;
}

bool Ticket::operator!=(Ticket const& autre) const{
    return autre.code_ != this->code_;
}