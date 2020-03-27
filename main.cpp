
#include <iostream>
#include <mutex>

#include "arbitre.h"

using namespace std;

int main()
{
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    //enum class player {BRUTAL_ , RAND, ALPHABETA, PLAYER} ;

    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a (9999, player::ALPHABETA, player::RAND, 100);
    // commence le challenge
    a.challenge();
    return 0;
}
