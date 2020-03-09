#include "ab_nathan.h"

Joueur_AB_Nathan::Joueur_AB_Nathan(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}


char Joueur_AB_Nathan::nom_abbrege() const
{
    return 'A';
}

int Joueur_AB_Nathan::max (int a, int b) {
	return ((a>=b)? a:b) ;
}
int Joueur_AB_Nathan::min (int a, int b) {
	return ((a<=b)? a:b) ;
}

int Joueur_AB_Nathan::alphabeta(Jeu jeu, bool E, int a, int b) {
	if(jeu.fini())
		if(E) return -1;
		else  return 1;
		
	int val;
	if(E){
		val = -999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			g.joue(i);
			val = max(val, alphabeta(g,!E,a,b));
			a = max(a,val);
			if(a>=b) break; 
		}
		return val;
	} else {
		val = 999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			g.joue(i);
			val = min(val, alphabeta(g,!E,a,b));
			b = min(b,val);
			if(b<=a) break;
		}
		return val;
	}
}

typedef std::pair<int,int> ab_return;
ab_return Joueur_AB_Nathan::alphabeta_with_move(Jeu jeu, bool E, int a, int b) {
	//n++;
	if(jeu.fini())
		if(E) return std::make_pair(-1,-1);
		else  return std::make_pair(1,-1);
		
	int val,mov=-1;
	if(E){
		val = -999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			g.joue(i);
			ab_return abr = alphabeta_with_move(g,!E,a,b);
			if(abr.first>val){
				val = abr.first;
				mov = i;
			}
			a = max(a,val);
			if(a>=b) break; 
		}
		return std::make_pair(val,mov);
	} else {
		val = 999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			g.joue(i);
			ab_return abr = alphabeta_with_move(g,!E,a,b);
			if(abr.first<val){
				val = abr.first;
				mov = i;
			}
			b = min(b,val);
			if(b<=a) break;
		}
		return std::make_pair(val,mov);
	}
}

void Joueur_AB_Nathan::recherche_coup(Jeu jeu, int &coup)
{
	
}
