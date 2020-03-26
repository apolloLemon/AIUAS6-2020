#include "search_matthew.h"
#include "../evaluations/eval.h"

#define FLAG(X) std::cout << X << std::endl
//#define FLAG(X) 

search_matthew::search_matthew(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



char search_matthew::nom_abbrege() const
{
    return 'M';
}

/* using std::min std::max for now
int std::max (int a, int b) {return ((a>=b)? a:b);}
int std::min (int a, int b) {return ((a<=b)? a:b);}
*/

typedef std::pair<int,int> ab_return;
ab_return alphabeta_with_move(Jeu jeu, bool E, int a, int b, int depth, int ab) {
	if(jeu.fini() || depth==0)
		return std::make_pair(eval_nathan(jeu,ab),-1);
	
	//nathan code
	int mult;
	if (ab==0) {mult=1;} else {mult=-1;};
	//


	int val,mov=-1;
	if(E){
		val = -INF_INT;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g = jeu;
			if(!g.coup_licite(i)) continue;

			g.joue(mult*(i+1)); //weird nathan operation
			ab_return abr = alphabeta_with_move(g,!E,a,b,depth-1, ab);
			if(abr.first>val){
				val = abr.first;
				mov = i;
			}
			a = std::max(a,val);
			if(a>=b) break; 
		}
		return std::make_pair(val,mov);
	} else {
		val = INF_INT;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g = jeu;
			if(!g.coup_licite(i)) continue;

			g.joue((-1)*mult*(i+1)); //weirder nathan operation
			ab_return abr = alphabeta_with_move(g,!E,a,b,depth-1, ab);
			if(abr.first<val){
				val = abr.first;
				mov = i;
			}
			b = std::min(b,val);
			if(b<=a) break;
		}

		return std::make_pair(val,mov);
	}
}
void search_matthew::recherche_coup(Jeu jeu, int &coup)
{
	int depth = DEPTH;
	//int n = 0;

	//nathan code 
	int tour = jeu._nb_tours;
	int ab = tour%2;
	//

	auto res= alphabeta_with_move(jeu, true,-INF_INT,INF_INT,depth,ab); 
	coup = res.second;
	FLAG("coup "<<coup<<" :> "<<res.first);
	//std::cout << n << "noeuds pour AB\n";
}





/*
typedef std::pair<int,std::stack<int>> pvs_return;
pvs_return PVS(Jeu jeu, bool E, int &a, int &b, int depth, int ab, movelist lpv) {
	if(jeu.fini() || depth==0)
		return std::make_pair(eval_nathan(jeu,ab),std::stack<int>());
	
	//nathan code
	int mult;
	if (ab==0) {mult=1;} else {mult=-1;};
	//


	int val;
	movelist mov;
	if(E){
		val = -INF_INT;
		int c;
		
		if(!lpv.empty()){
			c = lpv.top();
		}
		Jeu g = jeu; movelist l=lpv;
		if(g.coup_licite(c)){
			lpv.pop();
			g.joue(mult*(c+1));
			pvs_return abr = PVS(g,!E,a,b,depth-1, ab, l);
			if(abr.first>val){
				val = abr.first;
				mov = abr.second;
				mov.push(c);
			}
			a = std::max(a,val);
		}

		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g = jeu;
			if(!g.coup_licite(i) || i==c) continue;

			g.joue(mult*(i+1)); //weird nathan operation
			pvs_return abr = PVS(g,!E,a,b,depth-1, ab,std::stack<int>());
			if(abr.first>val){
				val = abr.first;
				mov = abr.second;
				mov.push(i);
			}
			a = std::max(a,val);
			if(a>=b) break; 
		}

		return std::make_pair(val,mov);
	} else {
		val = INF_INT;
		for(int i=0;i<jeu.nb_coups();i++){
			Jeu g = jeu;
			if(!g.coup_licite(i)) continue;

			g.joue((-1)*mult*(i+1)); //weirder nathan operation
			pvs_return abr = PVS(g,!E,a,b,depth-1, ab,lpv);
			if(abr.first<val){
				val = abr.first;
			}
			b = std::min(b,val);
			if(b<=a) break;
		}

	}
		return std::make_pair(val,mov);
}
void search_matthew::recherche_coup(Jeu jeu, int &coup)
{
	int depth = DEPTH;
	//int n = 0;

	//nathan code 
	int tour = jeu._nb_tours;
	int ab = tour%2;
	//
	int a = -INF_INT;
	int b = INF_INT;


	auto res= PVS(jeu, true,a,b,depth,ab,pv); 
	coup = res.second.top();
	pv=res.second;
	FLAG("coup "<<coup<<" :> "<<res.first);
	//std::cout << n << "noeuds pour AB\n";
}*/