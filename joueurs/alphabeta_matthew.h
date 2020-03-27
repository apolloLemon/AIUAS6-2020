#pragma once

#include "joueur.h"

typedef std::pair<int, int> ab_return;
#define INF_INT 999999
#define DEPTH 3

class Alphabeta_Matthew : public Joueur
{
public:
  	Alphabeta_Matthew(std::string nom, bool joueur);
  	char nom_abbrege() const override;

	ab_return alphabeta(Jeu jeu, bool E, int a, int b, int depth, int ab);
	int eval_nathan(Jeu jeu, int ab);

  	void recherche_coup(Jeu, int & coup) override;
};
