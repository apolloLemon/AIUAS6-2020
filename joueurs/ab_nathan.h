#pragma once


#include "joueur.h"

typedef std::pair<int,int> ab_return;

class Joueur_AB_Nathan : public Joueur
{
public:
  Joueur_AB_Nathan(std::string nom, bool joueur);
  char nom_abbrege() const override;

  void recherche_coup(Jeu, int & coup) override;

  int max(int, int);
  int min(int, int);

  int alphabeta(Jeu jeu, bool E, int a, int b);
  ab_return alphabeta_with_move(Jeu jeu, bool E, int a, int b);
};
