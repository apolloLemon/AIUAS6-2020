#pragma once


#include "joueur.h"


class search_matthew : public Joueur
{
public:
  search_matthew(std::string nom, bool joueur);
  char nom_abbrege() const override;

  void recherche_coup(Jeu, int & coup) override;
};
