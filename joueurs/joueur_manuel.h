#pragma once

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <utility>
// #include <mutex>
// #include <experimental/random>
#include "joueur.h"


class Joueur_Manuel : public Joueur
{

public:
    Joueur_Manuel(std::string nom,bool joueur);
    char nom_abbrege() const override;


    void recherche_coup(Jeu jeu, int & coup) override;
};

