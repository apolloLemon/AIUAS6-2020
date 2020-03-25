#include "eval.h"

// Evalue l'état d'un jeu
// ab : Indique si notre joueur est le joueur 1 (ab=0) ou 2 (ab=1)
int eval_nathan(Jeu jeu, int ab)
{
	// Récupère le tour, ici va être le n° du tour après avoir joué
	// (nb_tour++ dans Jeu::joue())
	int tour = jeu._nb_tours;
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
        if ((hauteur == 4 && col == 15) || // xxxx
	        (hauteur == 5 && col == 30) || // oxxxx
	        (hauteur == 6 && ((col == 60) || // ooxxxx
	        (col == 61))) // xoxxxx
        	)
        {
        	if(ab==0) {val+=99999;} else {val-=99999;}
        }
        else if ((hauteur == 3 && col == 7) || // xxx
	 		(hauteur == 4 && hauteur > 0 && col == 14) || // oxxx
	        (hauteur == 5 && ((col == 28) || // ooxxx
	        (col == 29))) // xoxxx
	        )
        {
        	if(ab==0) {val+=9999;} else {val-=9999;}
        }
        else if ((hauteur == 2 && col == 3) || // xx
	        (hauteur == 3 && hauteur > 0 && col == 6) || // oxx
	        (hauteur == 4 && ((col == 12) || // ooxx
	        (col == 13))) // xoxx
	        )
	    {
	    	if(ab==0) {val+=999;} else {val-=999;}
	    }

        if ((hauteur == 4  && col == 0) || // oooo
	        (hauteur == 5  && col == 1) || // xoooo
	        (hauteur == 6  && (col == 2 || // oxoooo
	        col == 3))    // xxoooo
	        )
        {
        	if(ab==1) {val+=99999;} else {val-=99999;}
        }
        else if ((hauteur == 3  && col == 0) || // ooo
	        (hauteur == 4  && col == 1) || // xooo
	        (hauteur == 5  && (col == 3 || // xxooo
	        col == 2))    // oxooo
	        )
        {
        	if(ab==1) {val+=9999;} else {val-=9999;}
        }
        else if ((hauteur == 2  && col == 0) || // oo
	        (hauteur == 3  && col == 1) || // xoo
	        (hauteur == 4  && (col == 3 || // xxoo
	        col == 2))    // oxoo
	        )
        {
        	//std::cout << "doubleO" << std::endl;
        	if(ab==1) {val+=999;} else {val-=999;}
        }
	}

	// Check horizontal
	// Pour chaque ligne, on check à quel point on se fait démonter
	int dual_x, dual_o;
	for (int j=0; j<MAX_HAUTEUR; j++)
	{
		dual_x = jeu._dual_x[j];
		dual_o = jeu._dual_o[j];

		// =========== X Evalutation ==============
		if (((dual_x & 1) && (dual_x & 2)  && (dual_x & 4)  && (dual_x & 8))  || 	// XXXX***
		    ((dual_x & 2) && (dual_x & 4)  && (dual_x & 8)  && (dual_x & 16)) || 	// *XXXX**
		    ((dual_x & 4) && (dual_x & 8)  && (dual_x & 16) && (dual_x & 32)) || 	// **XXXX*
		    ((dual_x & 8) && (dual_x & 16) && (dual_x & 32) && (dual_x & 64))		// ***XXXX
		    )
		{ if(ab == 0) {val+=99999;} else {val-=99999;} }

		if (((dual_x & 2)  && (dual_x & 4)  && (dual_x & 8)  && !((dual_x >> 0) & 1) && !((dual_x >> 4) & 1) && !((dual_o >> 0) & 1) && !((dual_o >> 4) & 1)) || 	// _XXX_**
		    ((dual_x & 4)  && (dual_x & 8)  && (dual_x & 16) && !((dual_x >> 1) & 1) && !((dual_x >> 5) & 1) && !((dual_o >> 1) & 1) && !((dual_o >> 5) & 1)) || 	// *_XXX_*
		    ((dual_x & 8)  && (dual_x & 16) && (dual_x & 32) && !((dual_x >> 2) & 1) && !((dual_x >> 6) & 1) && !((dual_o >> 2) & 1) && !((dual_o >> 6) & 1)) 	// **_XXX_
		    )
		{ if(ab == 0) {val+=49999;} else {val-=49999;} }

		if (((dual_x & 1)  && (dual_x & 2)  && (dual_x & 4)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)) || // XXX_***
			((dual_x & 2)  && (dual_x & 4)  && (dual_x & 8)  && (dual_o & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || // OXXX_**
			((dual_x & 2)  && (dual_x & 4)  && (dual_x & 8)  && (dual_o & 16) && !((dual_x >> 0) & 1) && !((dual_o >> 0) & 1))  || // _XXXO**
			((dual_x & 4)  && (dual_x & 8)  && (dual_x & 16) && (dual_o & 32) && !((dual_x >> 1) & 1) && !((dual_o >> 1) & 1))  || // *_XXXO*
			((dual_x & 4)  && (dual_x & 8)  && (dual_x & 16) && (dual_o & 2)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || // *OXXX_*
			((dual_x & 8)  && (dual_x & 16) && (dual_x & 32) && (dual_o & 64) && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1))  || // **_XXXO
			((dual_x & 8)  && (dual_x & 16) && (dual_x & 32) && (dual_o & 4)  && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1)) || // **OXXX_
		    ((dual_x & 16) && (dual_x & 32) && (dual_x & 64) && !((dual_x >> 3) & 1) && !((dual_o >> 3) & 1))  || 	// ***_XXX
		    ((dual_x & 1)  && (dual_x & 2)  && (dual_x & 8)  && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1))  || 	// XX_X***
		    ((dual_x & 1)  && (dual_x & 4)  && (dual_x & 8)  && !((dual_x >> 1) & 1) && !((dual_o >> 1) & 1))  || 	// X_XX***
		    ((dual_x & 2)  && (dual_x & 4)  && (dual_x & 16) && !((dual_x >> 3) & 1) && !((dual_o >> 3) & 1))  || 	// *XX_X**
		    ((dual_x & 2)  && (dual_x & 8)  && (dual_x & 16) && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1))  || 	// *X_XX**
		    ((dual_x & 4)  && (dual_x & 8)  && (dual_x & 32) && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || 	// **XX_X*
		    ((dual_x & 4)  && (dual_x & 16) && (dual_x & 32) && !((dual_x >> 3) & 1) && !((dual_o >> 3) & 1))  || 	// **X_XX*
		    ((dual_x & 8)  && (dual_x & 16) && (dual_x & 64) && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || 	// ***XX_X
		    ((dual_x & 8)  && (dual_x & 32) && (dual_x & 64) && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) 	// ***X_XX
		    )
		{ if(ab == 0) {val+=9999;} else {val-=9999;} }

		if (((dual_x & 2)  && (dual_x & 8)  && !((dual_x >> 0) & 1) && !((dual_o >> 0) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || // _X_X_**
			((dual_x & 4)  && (dual_x & 16) && !((dual_x >> 1) & 1) && !((dual_o >> 1) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || // *_X_X_*
			((dual_x & 8)  && (dual_x & 32) && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1) && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1)) || // **_X_X_
			((dual_x & 2)  && (dual_x & 4)  && !((dual_x >> 0) & 1) && !((dual_o >> 0) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || // _XX__**
		    ((dual_x & 4)  && (dual_x & 8)  && !((dual_x >> 1) & 1) && !((dual_o >> 1) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1) && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || // *_XX__*
		    ((dual_x & 4)  && (dual_x & 8)  && !((dual_x >> 0) & 1) && !((dual_o >> 0) & 1)  && !((dual_x >> 1) & 1)  && !((dual_o >> 1) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || // __XX_**
		    ((dual_x & 8)  && (dual_x & 16) && !((dual_x >> 1) & 1) && !((dual_o >> 1) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || // *__XX_*
		    ((dual_x & 8)  && (dual_x & 16) && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1) && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1)) || // **_XX__
		    ((dual_x & 16) && (dual_x & 32) && !((dual_x >> 2) & 1) && !((dual_o >> 2) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1)) 	 // **__XX_
		    )
		{ if(ab == 0) {val+=4999;} else {val-=4999;} }

		if (((dual_x & 1)  && (dual_x & 2)  && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1))  || // XX__***
		    ((dual_x & 32) && (dual_x & 64) && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) ||	// ***__XX
			((dual_x & 2)  && (dual_x & 4)  && !((dual_x >> 0) & 1)  && !((dual_o >> 0) & 1)  && !((dual_x >> 3) & 1) && !((dual_o >> 3) & 1) && (dual_o & 16)) || 	// _XX_O**
			((dual_x & 4)  && (dual_x & 8)  && !((dual_x >> 1) & 1)  && !((dual_o >> 1) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1) && (dual_o & 1) && (dual_o & 32)) || 	// O_XX_O*
			((dual_x & 8)  && (dual_x & 16) && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1) && (dual_o & 2) && (dual_o & 64)) || 	// *O_XX_O
			((dual_x & 16) && (dual_x & 32) && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1) && (dual_o & 4))  || 	// **O_XX_
			((dual_x & 2)  && (dual_x & 4)  && (dual_o & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1)) || 	// OXX__**
			((dual_x & 4)  && (dual_x & 8)  && (dual_o & 2)  && !((dual_x >> 4) & 1) && !((dual_o >> 4) & 1) && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1)) || 	// *OXX__*
			((dual_x & 8)  && (dual_x & 16) && (dual_o & 4)  && !((dual_x >> 5) & 1) && !((dual_o >> 5) & 1) && !((dual_x >> 6) & 1) && !((dual_o >> 6) & 1)) || 	// **OXX__
			((dual_x & 16) && (dual_x & 32) && (dual_o & 64) && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 3) & 1))  || 	// **__XXO
			((dual_x & 8)  && (dual_x & 16) && (dual_o & 32) && !((dual_x >> 1) & 1)  && !((dual_o >> 1) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 2) & 1))  || 	// *__XXO*
			((dual_x & 4)  && (dual_x & 8)  && (dual_o & 16) && !((dual_x >> 0) & 1)  && !((dual_o >> 0) & 1)  && !((dual_x >> 1) & 1)  && !((dual_o >> 1) & 1))		// __XXO**
		    )
		{ if(ab == 0) {val+=999;} else {val-=999;} }

		
		// =========== O Evalutation ==============
		if (((dual_o & 1) && (dual_o & 2)  && (dual_o & 4)  && (dual_o & 8))  || 	// OOOO***
		    ((dual_o & 2) && (dual_o & 4)  && (dual_o & 8)  && (dual_o & 16)) || 	// *OOOO**
		    ((dual_o & 4) && (dual_o & 8)  && (dual_o & 16) && (dual_o & 32)) || 	// **OOOO*
		    ((dual_o & 8) && (dual_o & 16) && (dual_o & 32) && (dual_o & 64))		// ***OOOO
		    )
		{ if(ab == 1) {val+=99999;} else {val-=99999;} }

		if (((dual_o & 2)  && (dual_o & 4)  && (dual_o & 8)  && !((dual_o >> 0) & 1) && !((dual_o >> 4) & 1) && !((dual_x >> 0) & 1) && !((dual_x >> 4) & 1)) || 	// _OOO_**
		    ((dual_o & 4)  && (dual_o & 8)  && (dual_o & 16) && !((dual_o >> 1) & 1) && !((dual_o >> 5) & 1) && !((dual_x >> 1) & 1) && !((dual_x >> 5) & 1)) || 	// *_OOO_*
		    ((dual_o & 8)  && (dual_o & 16) && (dual_o & 32) && !((dual_o >> 2) & 1) && !((dual_o >> 6) & 1) && !((dual_x >> 2) & 1) && !((dual_x >> 6) & 1)) 	// **_OOO_
		    )
		{ if(ab == 1) {val+=49999;} else {val-=49999;} }

		if (((dual_o & 1)  && (dual_o & 2)  && (dual_o & 4)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)) || // OOO_***
			((dual_o & 2)  && (dual_o & 4)  && (dual_o & 8)  && (dual_x & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || // XOOO_**
			((dual_o & 2)  && (dual_o & 4)  && (dual_o & 8)  && (dual_x & 16) && !((dual_o >> 0) & 1)  && !((dual_x >> 0) & 1))  || // _OOOX**
			((dual_o & 4)  && (dual_o & 8)  && (dual_o & 16) && (dual_x & 32) && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1))  || // *_OOOX*
			((dual_o & 4)  && (dual_o & 8)  && (dual_o & 16) && (dual_x & 2)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || // *XOOO_*
			((dual_o & 8)  && (dual_o & 16) && (dual_o & 32) && (dual_x & 64) && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1))  || // **_OOOX
			((dual_o & 8)  && (dual_o & 16) && (dual_o & 32) && (dual_x & 4)  && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1)) || // **XOOO_
		    ((dual_o & 16) && (dual_o & 32) && (dual_o & 64) && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1))  || 	// ***_OOO
		    ((dual_o & 1)  && (dual_o & 2)  && (dual_o & 8)  && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1))  || 	// OO_O***
		    ((dual_o & 1)  && (dual_o & 4)  && (dual_o & 8)  && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1))  || 	// O_OO***
		    ((dual_o & 2)  && (dual_o & 4)  && (dual_o & 16) && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1))  || 	// *OO_O**
		    ((dual_o & 2)  && (dual_o & 8)  && (dual_o & 16) && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1))  || 	// *O_OO**
		    ((dual_o & 4)  && (dual_o & 8)  && (dual_o & 32) && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || 	// **OO_O*
		    ((dual_o & 4)  && (dual_o & 16) && (dual_o & 32) && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1))  || 	// **O_OO*
		    ((dual_o & 8)  && (dual_o & 16) && (dual_o & 64) && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || 	// ***OO_O
		    ((dual_o & 8)  && (dual_o & 32) && (dual_o & 64) && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1))		// ***O_OO
		    )
		{ if(ab == 1) {val+=9999;} else {val-=9999;} }

		if (((dual_o & 2)  && (dual_o & 8)  && !((dual_o >> 0) & 1) && !((dual_x >> 0) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || // _O_O_**
			((dual_o & 4)  && (dual_o & 16) && !((dual_o >> 1) & 1) && !((dual_x >> 1) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || // *_O_O_*
			((dual_o & 8)  && (dual_o & 32) && !((dual_o >> 2) & 1) && !((dual_x >> 2) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1) && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1)) || // **_O_O_
			((dual_o & 2)  && (dual_o & 4)  && !((dual_o >> 0) & 1) && !((dual_x >> 0) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || // _OO__**
		    ((dual_o & 4)  && (dual_o & 8)  && !((dual_o >> 1) & 1) && !((dual_x >> 1) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1) && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || // *_OO__*
		    ((dual_o & 4)  && (dual_o & 8)  && !((dual_o >> 0) & 1) && !((dual_x >> 0) & 1)  && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || // __OO_**
		    ((dual_o & 8)  && (dual_o & 16) && !((dual_o >> 1) & 1) && !((dual_x >> 1) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || // *__OO_*
		    ((dual_o & 8)  && (dual_o & 16) && !((dual_o >> 2) & 1) && !((dual_x >> 2) & 1)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1) && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1)) || // **_OO__
		    ((dual_o & 16) && (dual_o & 32) && !((dual_o >> 2) & 1) && !((dual_x >> 2) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1)) 	 // **__OO_
		    )
		{ if(ab == 1) {val+=4999;} else {val-=4999;} }

		if (((dual_o & 1)  && (dual_o & 2)  && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 3) & 1) && !((dual_x >> 3) & 1))  || // OO__***
		    ((dual_o & 32) && (dual_o & 64) && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) ||	// ***__OO
			((dual_o & 2)  && (dual_o & 4)  && !((dual_o >> 0) & 1)  && !((dual_x >> 0) & 1)  && !((dual_o >> 3) & 1) && !((dual_x >> 3) & 1) && (dual_x & 16)) || 	// _OO_X**
			((dual_o & 4)  && (dual_o & 8)  && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1) && (dual_x & 1) && (dual_x & 32)) || 	// X_OO_X*
			((dual_o & 8)  && (dual_o & 16) && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1) && (dual_x & 2) && (dual_x & 64)) || 	// *X_OO_X
			((dual_o & 16) && (dual_o & 32) && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1) && (dual_x & 4))  || 	// **X_OO_
			((dual_o & 2)  && (dual_o & 4)  && (dual_x & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1)) || 	// XOO__**
			((dual_o & 4)  && (dual_o & 8)  && (dual_x & 2)  && !((dual_o >> 4) & 1) && !((dual_x >> 4) & 1) && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1)) || 	// *XOO__*
			((dual_o & 8)  && (dual_o & 16) && (dual_x & 4)  && !((dual_o >> 5) & 1) && !((dual_x >> 5) & 1) && !((dual_o >> 6) & 1) && !((dual_x >> 6) & 1)) || 	// **XOO__
			((dual_o & 16) && (dual_o & 32) && (dual_x & 64) && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1)  && !((dual_o >> 3) & 1)  && !((dual_x >> 3) & 1))  || 	// **__OOX
			((dual_o & 8)  && (dual_o & 16) && (dual_x & 32) && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1)  && !((dual_o >> 2) & 1)  && !((dual_x >> 2) & 1))  || 	// *__OOX*
			((dual_o & 4)  && (dual_o & 8)  && (dual_x & 16) && !((dual_o >> 0) & 1)  && !((dual_x >> 0) & 1)  && !((dual_o >> 1) & 1)  && !((dual_x >> 1) & 1))		// __OOX**
		    )
		{ if(ab == 1) {val+=999;} else {val-=999;} }

	}

    return val;
}

int old_eval(Jeu jeu, int ab)
{
	// Récupère le tour, ici va être le n° du tour après avoir joué
	// (nb_tour++ dans Jeu::joue())
	int tour = jeu._nb_tours;
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
        	if(ab==1) {val+=99999;} else {val-=99999;}
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
	    	if(ab==1) {val+=9;} else {val-=9;}
	    }

        if ((hauteur == 3  && col == 0) || // oooo
	        (hauteur == 4  && col == 1) || // xoooo
	        (hauteur == 5  && (col == 2 || // oxoooo
	        col == 3))    // xxoooo
	        )
        {
        	if(ab==1) {val-=99999;} else {val+=99999;}
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
        	if(ab==1) {val-=9;} else {val+=9;}
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
		{ if(tour%2 == ab) {val-=99999;} else {val+=99999;} }

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
		{ if(tour%2 == ab) {val-=9;} else {val+=9;} }
	}

    return val;
}