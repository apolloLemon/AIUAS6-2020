
#include <iostream>
#include <mutex>

#include "arbitre.h"

using namespace std;

int main()
{
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    //enum class player {BRUTAL_ , RAND, A_NATHAN, S_MATTHEW, PLAYER} ;

    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a (9999, player::S_MATTHEW, player::PLAYER, 2);
    // commence le challenge
    a.challenge();
    return 0;
}
