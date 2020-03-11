#include "ab_nathan.h"
#include "../evaluations/eval.h"

Joueur_AB_Nathan::Joueur_AB_Nathan(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}

char Joueur_AB_Nathan::nom_abbrege() const { return 'A'; }

int max (int a, int b) { return ((a>=b)? a:b); }
int min (int a, int b) { return ((a<=b)? a:b); }

// Algo minimax classique avec profondeur
// ab représente l'indicateur de quel joueur est Alpha-Beta
int minimax(Jeu jeu, int depth, bool maximizingPlayer, int ab)
{
	if (depth==0 or jeu.etat()==ALIGNEMENT)
	{
		return eval_nathan(jeu, ab);
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

	int tour = jeu._nb_tours;
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
