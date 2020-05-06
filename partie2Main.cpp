#include "headers/vConsigne.hpp"
#include "headers/Ticket.hpp"
#include "headers/vBagage.hpp"
#include "headers/vMalette.hpp"
#include "headers/vCylindre.hpp"
#include "headers/vDemiSphere.hpp"

#include <iostream>
#include <vector>
#include <memory>

std::string conversionBoolString(bool b) {
    return (b ? "vrai" : "faux");
}

int main() {

    /** 
     * TAPER "make mainPartie2" dans un terminal pour compiler cette partie.
    */

    srand(time(NULL));

    // TESTS

    // Consigne avec tableaux de tailles différentes

    try {
        vConsigne consigne({1,2,3}, {15}); // Tableaux de tailles différentes.

    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Consigne avec tableaux de taille nulle.

    try {
        vConsigne consigne({}, {}); // Aucune valeur dans les tableaux.
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Consigne avec l'une des valeurs des tableaux <= 0.

    try {
        vConsigne consigne({10, 12, -1}, {3, 4, 5}); // Valeur inférieure à 0 impossible.
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Dépot d'un bagage trop grand.

    try {
        vConsigne consigne({5, 10, 15}, {1, 2, 3});
        vBagage* malette = new vMalette("Malette trop grande", "Decathlon", 20, 30, 40); // Volume = 24 litres.

        Ticket ticketMalette = consigne.deposerBagage(malette); // Aucun casier de taille suffisante disponible.
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Dépot d'un bagage dans une consigne déjà pleine.

    try {
        vConsigne consigne({30}, {1});

        vBagage* malette = new vMalette("Malette de bonne taille", "Decathlon", 20, 30, 40); // Volume = 24 litres.
        vBagage* sacCylindrique = new vCylindre("Sac cylindrique", "Ikea", 15, 35); // Volume ~= 24.74 litres.

        std::cout << "La consigne est-elle pleine avant le premier dépot ? " << conversionBoolString(consigne.estPleine()) << std::endl;
        Ticket ticketMalette = consigne.deposerBagage(malette);
        std::cout << "La consigne est-elle pleine après le premier dépot ? " << conversionBoolString(consigne.estPleine()) << std::endl;
        Ticket ticketSac = consigne.deposerBagage(sacCylindrique); // Aucun casier de taille suffisante disponible.
 
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Retrait avec un ticket n'ayant pas été initialisé par la consigne.

    try {

        vConsigne consigne({30}, {5});

        vBagage* malette = new vMalette("Malette de bonne taille", "Decathlon", 20, 30, 40); // Volume = 24 litres.

        Ticket ticketMalette = consigne.deposerBagage(malette);
        Ticket ticketPirate;

        vBagage* bagageRetire = consigne.retirerBagage(ticketPirate); // Bagage non trouvé.


    } catch(std::exception const& e){
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Retrait avec un ticket ayant déjà été utilisé.

    try {

        vConsigne consigne({30}, {5});

        vBagage* malette = new vMalette("Malette de bonne taille", "Decathlon", 20, 30, 40); // Volume = 24 litres.

        Ticket ticketMalette = consigne.deposerBagage(malette);
        vBagage* bagageRetire = consigne.retirerBagage(ticketMalette);

        vBagage* bagageRetireUneDeuxiemeFois = consigne.retirerBagage(ticketMalette); // Bagage non trouvé.

    } catch(std::exception const& e){
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Initialisation d'un bagage avec un volume négatif.

    try {

        vConsigne consigne({15}, {1});

        vBagage* malette = new vMalette("Malette de volume négatif", "Decathlon", -10, 10, 10); // Le volume du bagage ne peut pas être inférieur à 0.
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    // Gestion normale d'une consigne, sans erreurs.

    try {

        // Initialisation d'une consigne de 3 casiers de volumes différents (l'ordre des volumes dans la liste n'est pas important lors de l'initialisation de la consigne).
        vConsigne consigne({10, 20, 5}, {1, 1, 2});
        consigne.d_afficherCasiersLibres();
        std::cout << "La consigne est-elle pleine ? " << conversionBoolString(consigne.estPleine()) << std::endl;

        vBagage* malette1 = new vMalette("Petite malette 1", "Eastpack", 5, 10, 15); // Volume = 0.75 litres.
        vBagage* malette2 = new vMalette("Petite malette 2", "Eastpack", 10, 15, 20); // Volume = 3 litres.
        vBagage* petitSac1 = new vCylindre("Petit sac 1", "Ikea", 10, 20); // Volume ~= 1.57 litres.
        vBagage* petitSac2 = new vCylindre("Petit sac 2", "Ikea", 12, 18); // Volume ~= 2.04 litres.


        Ticket tMalette1 = consigne.deposerBagage(malette1);
        consigne.d_afficherCasiersLibres(); // Le premier casier de 5 litres a été choisi (tous les index libérations sont à 0 donc pas de priorité).
        vBagage* recuperationMalette1 = consigne.retirerBagage(tMalette1);
        std::cout << "Le bagage récupéré s'appelle " << recuperationMalette1->getNom() << std::endl; // "Petit malette 1".
        consigne.d_afficherCasiersLibres(); // Le casier qui avait été choisi est placé derrière tout ceux du même volume que lui.

        Ticket tMalette2 = consigne.deposerBagage(malette2);
        consigne.d_afficherCasiersLibres(); // Le casier avec l'index libération le plus faible (0 < 1) a donc été choisi.
        Ticket tPetitSac1 = consigne.deposerBagage(petitSac1);
        consigne.d_afficherCasiersLibres(); // Le dernier casier de 5 litres a été choisi.
        Ticket tPetitSac2 = consigne.deposerBagage(petitSac2);
        consigne.d_afficherCasiersLibres(); // Plus aucun casier de 5 litres, celui de 10 litres a donc été choisi.

        // EVOLUTION DE L'INDEX LIBERATION.

        vBagage* recuperationPetitSac1 = consigne.retirerBagage(tPetitSac1);
        consigne.d_afficherCasiersLibres(); 

        vBagage* recuperationPetitSac2 = consigne.retirerBagage(tPetitSac2);
        consigne.d_afficherCasiersLibres();

        vBagage* recuperationMalette2 = consigne.retirerBagage(tMalette2);
        consigne.d_afficherCasiersLibres();

        // Le casier numéro 4, bien qu'ayant été rempli AVANT le numéro 3 (de même volume), est classé avant le numéro 3 car ce dernier a été libéré APRES le numéro 4. 
        // Nous sommes donc assurés que c'est bien le casier ayant été utilisé il y a le plus longtemps qui va être choisi entre deux casiers de même volume
        // Nous pouvons également remarqué que l'index libération est bien unique pour chaque casier dès qu'il est utilisé au moins une fois.

    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}