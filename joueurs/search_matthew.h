#pragma once


#include "joueur.h"
#include <stack>

typedef std::stack<int> movelist;
#define INF_INT 999999
#define DEPTH 3

class search_matthew : public Joueur
{
public:
  search_matthew(std::string nom, bool joueur);
  char nom_abbrege() const override;

  void recherche_coup(Jeu, int & coup) override;

  movelist pv;
};
