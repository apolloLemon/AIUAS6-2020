#include "jeu.h"
#include <iostream>

Jeu::Jeu(int graine) {
  reset();
}

void Jeu::reset() {
  int i = 0;
  for (i = 0; i < MAX_HAUTEUR; i++) {
    _dual_o[i] = 0;
    _dual_x[i] = 0;
  }
  for (i = 0; i < MAX_LARGEUR; i++) {
    _puissance[i] = 1;
    _plateau._hauteur[i] = 0;
    _plateau._pions[i] = 0;
    _tab[i] = i; 
  }
  _alignement = false;
  _nombre = MAX_LARGEUR;
  _etat = PARTIE_NON_TERMINEE;
  _nb_tours = 0;
}

bool Jeu::coup_licite(int coup) {
  return !((coup < 0) || (coup >= _nombre));
}
  
void Jeu::joue(int indice_coup) {
  _nb_tours++;
  int indice_relatif =  abs(indice_coup)-1;
  int indice_absolu = _tab[indice_relatif];

  int hauteur = _plateau._hauteur[indice_absolu];
  
  if (hauteur == MAX_HAUTEUR-1) {
    _nombre--;
    int i;
    for (i = indice_relatif ; i < _nombre ; i++) {
      _tab[i] = _tab[i+1];
    }
  }
  

  if (indice_coup > 0) {
    _plateau._pions[indice_absolu] += _puissance[indice_absolu];

            _dual_x[hauteur] = _dual_x[hauteur] + (1 << indice_absolu);
  }
  else {
    _dual_o[hauteur] = _dual_o[hauteur] + (1 << indice_absolu);
  }
  _puissance[indice_absolu] = _puissance[indice_absolu] << 1;
  _plateau._hauteur[indice_absolu]++;

  

  // Calcul explicite pour un plateau 7 x 6

  // vertical
  int le_coup = _plateau._pions[indice_absolu];
  if (indice_coup > 0) {
    if ((hauteur == 3 && le_coup == 15) || // xxxx
  	(hauteur == 4 && hauteur > 0 && le_coup == 30) || // oxxxx
  	(hauteur == 5 && ((le_coup == 60) || // ooxxxx
  			       (le_coup == 61))) // xoxxxx
  	) { _etat = ALIGNEMENT; return;}
  }
  else {
    if ((hauteur == 3  && le_coup == 0) || // oooo
  	(hauteur == 4  && le_coup == 1) || // xoooo
  	(hauteur == 5  && (le_coup == 2 || // oxoooo
  			   le_coup == 3))    // xxoooo
  	) { _etat = ALIGNEMENT; return;}
  }
  // horizontal
  int dual;
  if (indice_coup > 0) 
    dual = _dual_x[hauteur];
  else 
    dual = _dual_o[hauteur];
  
  if ((indice_absolu < 4 && (dual & 1) && (dual & 2) && (dual & 4) && (dual & 8)) || // ????___
  	((indice_absolu > 0 && indice_absolu < 5) && (dual & 2) && (dual & 4) && (dual & 8) && (dual & 16)) || // _????__
  	((indice_absolu > 1 && indice_absolu < 6) && (dual & 4) && (dual & 8) && (dual & 16) && (dual & 32)) || // __????_
  	(indice_absolu > 2 && (dual & 8) && (dual & 16) && (dual & 32) && (dual & 64)) // ___????
      )
    { _etat = ALIGNEMENT; return;}

  if (_nb_tours == MAX_HAUTEUR * MAX_LARGEUR) {_etat = PARTIE_NULLE;}
  
}

int Jeu::nb_coups() {
  return _nombre;
}

bool Jeu::fini() {
  return (_etat != PARTIE_NON_TERMINEE);
}

int& Jeu::operator[](int i) {
  if ((i < 0) || (i > _nombre)) {
    std::cout << std::endl << "Erreur de limite."<<'\n';}
  return _tab[i];
}


Plateau* Jeu::plateau() {
  return & _plateau;
}

bool Jeu::partie_nulle() {
  return (_etat == PARTIE_NULLE);
}

std::ostream& operator<<( std::ostream &flux, Plateau const& plateau ) {
  plateau.afficher(flux);
  return flux;
}


void Plateau::afficher( std::ostream &flux) const {
  int i,j;
  int puissance = 32;
  Plateau p(*this);

  for (i=5 ; i>=0 ; i--) {
    flux << '|';
    for (j=0 ; j< MAX_LARGEUR ; j++) {
      if (p._pions[j] >= puissance) {
	flux << "x|";
	p._pions[j] -= puissance;
      }
      else
	if (p._hauteur[j] > i)
	  {
	    flux << "o|";
	  }
	else {
	  flux << " |";
	}
    }
    puissance = puissance >> 1;
    flux << std::endl;
  }
  flux << '|';
  for (j=0 ; j<MAX_LARGEUR ; j++) {
    flux << j+1 << '|';
  }
  flux << std::endl;
}
void Jeu::print_coups(){}
