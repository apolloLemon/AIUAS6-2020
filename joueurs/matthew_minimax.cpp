#include "joueur_minimax_.h"


Joueur_MiniMax_::Joueur_MiniMax_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



char Joueur_MiniMax_::nom_abbrege() const
{
    return 'M';
}

int _max(int a, int b) {
	return ((a>=b)? a:b) ;
}
int _min(int a, int b) {
	return ((a<=b)? a:b) ;
}

int minimax(Jeu jeu, bool E) {
	//std::cout << "minimax ";
	//std::cout << (E? "Existantiel" : "Universel") << std::endl;
	//jeu.print_coups();
	if(jeu.fini())
		if(E) return -1;
		else  return 1;

	int val;
	if(E){
		val = -999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			//std::cout << "E Forloop: "<<i<<" verifie le coup: "<<jeu[i]<<std::endl;
			//if(!g.coup_licite(i)) continue;
			g.joue(i);
			val = _max(val, minimax(g,!E));
		}
		return val;
	} else {
		val = 999;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g(jeu.etat());
			//std::cout << "!E Forloop: "<<i<<" verifie le coup: "<<jeu[i]<<std::endl;
			
			//if(!g.coup_licite(i)) continue;
			g.joue(i);
			val = _min(val, minimax(g,!E));
		}
		return val;
	}
}

void Joueur_MiniMax_::recherche_coup(Jeu jeu, int &coup)
{
	int val=-999;
	for(int i=0;i<jeu.nb_coups();i++){
		Jeu g(jeu.etat());
		if(!g.coup_licite(i)) continue;
		g.joue(i);
		int mm = minimax(g,false);
		if(mm>val){
			coup=i;
			val=mm;
		}
	}
}
