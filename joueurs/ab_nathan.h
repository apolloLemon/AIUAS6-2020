#pragma once

#include "joueur.h"

class Joueur_AB_Nathan : public Joueur
{
public:
	Joueur_AB_Nathan(std::string nom, bool joueur);
	char nom_abbrege() const override;

	void recherche_coup(Jeu, int & coup) override;
};
