#include "ab_nathan.h"

Joueur_AB_Nathan::Joueur_AB_Nathan(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}

char Joueur_AB_Nathan::nom_abbrege() const { return 'A'; }

int max (int a, int b) { return ((a>=b)? a:b); }
int min (int a, int b) { return ((a<=b)? a:b); }

// Evalue l'état d'un jeu
// ab : Indique si notre joueur est le joueur 1 (ab=0) ou 2 (ab=1)
int eval(Jeu jeu, int ab)
{
	// Récupère le tour, ici va être le n° du tour après avoir joué
	// (nb_tour++ dans Jeu::joue())
	int tour = jeu.getTours();
	int val = 0;

	// Si tout est rempli, alors égalité !
	if (tour == MAX_HAUTEUR * MAX_LARGEUR) {return val;}

	// Check vertical
	// Pour chaque colonne on vérifie la composition et on défini à quel point on
	// est dans la merde
	for(int i=0; i<MAX_LARGEUR; i++)
	{
		int col = jeu._plateau._pions[i];
		int hauteur = jeu._plateau._hauteur[i];
        if ((hauteur == 3 && col == 15) || // xxxx
	        (hauteur == 4 && hauteur > 0 && col == 30) || // oxxxx
	        (hauteur == 5 && ((col == 60) || // ooxxxx
	        (col == 61))) // xoxxxx
        	)
        {
        	if(ab==1) {val+=999;} else {val-=999;}
        }
        else if ((hauteur == 2 && col == 7) || // xxx
	 		(hauteur == 3 && hauteur > 0 && col == 14) || // oxxx
	        (hauteur == 4 && ((col == 28) || // ooxxx
	        (col == 29))) // xoxxx
	        )
        {
        	if(ab==1) {val+=499;} else {val-=499;}
        }
        else if ((hauteur == 1 && col == 3) || // xx
	        (hauteur == 2 && hauteur > 0 && col == 6) || // oxx
	        (hauteur == 3 && ((col == 12) || // ooxx
	        (col == 13))) // xoxx
	        )
	    {
	    	if(ab==1) {val+=49;} else {val-=49;}
	    }

        if ((hauteur == 3  && col == 0) || // oooo
	        (hauteur == 4  && col == 1) || // xoooo
	        (hauteur == 5  && (col == 2 || // oxoooo
	        col == 3))    // xxoooo
	        )
        {
        	if(ab==1) {val-=999;} else {val+=999;}
        }
        else if ((hauteur == 2  && col == 0) || // ooo
	        (hauteur == 3  && col == 1) || // xooo
	        (hauteur == 4  && (col == 3 || // xxooo
	        col == 2))    // oxoooo
	        )
        {
        	if(ab==1) {val-=499;} else {val+=499;}
        }
        else if ((hauteur == 1  && col == 0) || // oo
	        (hauteur == 2  && col == 1) || // xoo
	        (hauteur == 3  && (col == 3 || // xxoo
	        col == 2))    // oxoo
	        )
        {
        	//std::cout << "doubleO" << std::endl;
        	if(ab==1) {val-=49;} else {val+=49;}
        }
	}

	// Check horizontal
	// Pour chaque ligne, on check à quel point on se fait démonter
	int dual;
	for (int j=0; j<MAX_HAUTEUR; j++)
	{
		if (tour%2 == 1)
			dual = jeu._dual_x[j];
		else
			dual = jeu._dual_o[j];

		if (((dual & 1) && (dual & 2) && (dual & 4) && (dual & 8)) || // ????___
		    ((dual & 2) && (dual & 4) && (dual & 8) && (dual & 16)) || // _????__
		    ((dual & 4) && (dual & 8) && (dual & 16) && (dual & 32)) || // __????_
		    ((dual & 8) && (dual & 16) && (dual & 32) && (dual & 64)) // ___????
		    )
		{ if(tour%2 == ab) {val-=999;} else {val+=999;} }

			else if (((dual & 1) && (dual & 2) && (dual & 4) && (dual ^ 8)) || // ???____
		    ((dual & 2) && (dual & 4) && (dual & 8) && (dual ^ 1) && (dual ^ 16)) || // _???___
		    ((dual & 4) && (dual & 8) && (dual & 16) && (dual ^ 2) && (dual ^ 32)) || // __???__
		    ((dual & 8) && (dual & 16) && (dual & 32) && (dual ^ 4) && (dual ^ 64)) || // ___???_
		    ((dual & 16) && (dual & 32) && (dual & 64) && (dual ^ 8)) // ____???
		    )
		{ if(tour%2 == ab) {val-=499;} else {val+=499;} }

			else if (((dual & 1) && (dual & 2) && (dual ^ 4)) || // ??_____
		    ((dual & 2) && (dual & 4) && (dual ^ 1) && (dual ^ 8)) || // _??____
		    ((dual & 4) && (dual & 8) && (dual ^ 2) && (dual ^ 16)) || // __??___
		    ((dual & 8) && (dual & 16) && (dual ^ 4) && (dual ^ 32))  || // ___??__
		    ((dual & 16) && (dual & 32) && (dual ^ 8) && (dual ^ 64)) || // ____??_
		    ((dual & 32) && (dual & 64) && (dual ^ 16)) // _____??
		    )
		{ if(tour%2 == ab) {val-=49;} else {val+=49;} }
	}

    return val;
}

// Algo minimax classique avec profondeur
// ab représente l'indicateur de quel joueur est Alpha-Beta
int minimax(Jeu jeu, int depth, bool maximizingPlayer, int ab)
{
	if (depth==0 or jeu.etat()==ALIGNEMENT)
	{
		return eval(jeu, ab);
	}
	int val;
	Jeu g = jeu;
	int mult;
	if (ab==0) {mult=1;} else {mult=-1;};
	if (maximizingPlayer)
	{
		val = -9999;
		for(int i=0; i<7; i++)
		{
			if(g.coup_licite(i)) {
				g = jeu;
				g.joue(mult*(i+1));
				val = max(val, minimax(g, depth-1, false, ab));
			}
		}
		return val;
	}
	else
	{
		val = 9999;
		for (int i=0; i<7; i++) {
			if(jeu.coup_licite(i)) {
				g = jeu;
				g.joue((-1)*mult*(i+1));
				val = min(val, minimax(g, depth-1, true, ab));
			}
		}
		return val;
	}
}

// Pour chaque coup possible, on lance un minimax et on prend le meilleur
void Joueur_AB_Nathan::recherche_coup(Jeu jeu, int &coup)
{
	// 100% win : depth=4 avec 1000ms pour le mutex
	// Si Depth à 3 alors on gagne contre Brutal mais pas tout le temps contre RAND

	coup = 0;
	
	Jeu g = jeu;

	int tour = jeu.getTours();
	int ab = tour%2;
	int mult = 1;
	int mm = 0;
	if (ab == 1) { mult=-1; }
	int val = -9999; int tmp = val;

	for (int i=0; i<7; i++)
	{
		if (g.coup_licite(i))
		{
			g = jeu;
			g.joue(mult*(i+1));
			mm = minimax(g, 3, false, ab);
			std::cout << "\tCoup " << i << ": " << mm << std::endl;
			val = max(val, mm);
			if (val>tmp) { tmp = val; coup = i; }
		}
	}
}
