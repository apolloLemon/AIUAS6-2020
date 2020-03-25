#include "ab_nathan.h"
#include "../evaluations/eval.h"

#define INF_INT 999999

Joueur_AB_Nathan::Joueur_AB_Nathan(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}

char Joueur_AB_Nathan::nom_abbrege() const { return 'A'; }

int max (int a, int b) { return ((a>=b)? a:b); }
int min (int a, int b) { return ((a<=b)? a:b); }

// Algo minimax classique avec profondeur
// ab représente l'indicateur de quel joueur est Alpha-Beta
int alphabeta(Jeu jeu, int alpha, int beta, int depth, bool maximizingPlayer, int ab)
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
		val = -INF_INT;
		for(int i=0; i<7; i++)
		{
			if(g.coup_licite(i)) {
				g = jeu;
				g.joue(mult*(i+1));
				val = max(val, alphabeta(g, alpha, beta, depth-1, false, ab));
				if (val >= beta) { return val; }
				alpha = max(alpha, val);
			}
		}
	}
	else
	{
		val = INF_INT;
		for (int i=0; i<7; i++) {
			if(jeu.coup_licite(i)) {
				g = jeu;
				g.joue((-1)*mult*(i+1));
				val = min(val, alphabeta(g, alpha, beta, depth-1, true, ab));
				if (alpha >= val) { return val; }
				beta = min(beta, val);
			}
		}
	}
	return val;
}

// Pour chaque coup possible, on lance un minimax et on prend le meilleur
void Joueur_AB_Nathan::recherche_coup(Jeu jeu, int &coup)
{
	// 100% win : depth=4 avec 1000ms pour le mutex
	// Si Depth à 3 alors on gagne contre Brutal mais pas tout le temps contre RAND
	int depth = 2;
	coup = -1;
	
	Jeu g = jeu;

	int tour = jeu._nb_tours;
	int ab = tour%2;
	int mult = 1;
	int mm = 0;
	if (ab == 1) { mult=-1; }
	int val = -INF_INT-1; int tmp = val;

	std::cout << "ab: " << ab << std::endl;
	for (int i=0; i<7; i++)
	{
		if (g.coup_licite(i))
		{
			g = jeu;
			g.joue(mult*(i+1));
			mm = alphabeta(g, -INF_INT, INF_INT, depth, false, ab);
			std::cout << "\tCoup " << i << ": " << mm << std::endl;
			std::cout << "\tHauteur " << i << ": " << g._plateau._hauteur[i] << std::endl;
			val = max(val, mm);
			if (val>tmp) { tmp = val; coup = i; }
		}
	}
}
