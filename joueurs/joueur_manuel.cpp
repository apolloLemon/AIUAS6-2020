#include "joueur_manuel.h"

Joueur_Manuel::Joueur_Manuel(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



char Joueur_Manuel::nom_abbrege() const
{
    return 'P';
}

void Joueur_Manuel::recherche_coup(Jeu jeu, int &coup)
{
  //  coup = std::experimental::randint(0, jeu.nb_coups()-1);
  std::cout << "Choisis coup (0 is first legal col):";
  std::cin >> coup;
}
