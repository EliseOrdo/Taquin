#include "jeu.h"
#include <iomanip> // pour setw dans affichage.


/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g){
  int res = -1;
  return res;
  }

int proportion(const Grille &g){
  int res = -1;
  return res;
  }

int cible(const Grille &g){
  int res = -1;
  return res; 
  }

int dimension(const Grille &g){
  //Verifie que la grille est bien carree
  size_t dim = g.table.size();
  if (dim == 0){
    cerr << "La grille est vide" << endl;
    return -1;
  }
  for (size_t i = 0; i < dim; i += 1){
    if (g.table.at(i).size() != dim){
      cerr << "La grille n'est pas un carre" << endl;
      return -1;
    }
  }
  // Renvoie la dimension
  return dim;
  }

int score(const Grille &g){
  int res = -1;
  return res;
  }

bool succes(const Grille &g){ 
  return false;
  }

bool init(Grille &g, int dimension, int cible, int proportion) {
  bool res = false;
  // a faire
  return res;
}

// Ne pas oublier de vérifier la validité des paramètres !
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion){
  size_t dim = dimension(g);
  // Verification de la validite des parametres
  if(dim <= 0){
    return -1;
  }
  //Initialisation de la grille
  g.table = v;
  return true;
}


int droite(Grille &g){
  int res = -1;
  return res;
  }

int gauche(Grille &g)
{ int res = -1;
return res;
}

int haut(Grille &g){
  int res = -1;
  return res;
  }

int bas(Grille &g){
  int res = -1;
  return res;
  }


/*		 Pour les extensions éventuelles */
void sauve(const Grille &g, string filename) {

}


void restaure(Grille &g, string filename) {

}


/*
 * 		Fonctions mise à disposition. Pas de raison d'y toucher !
 *	Rappel: la fonction main() est dans le fichier test.cpp
 */	

void affiche (const Grille &g) {
  int i, j, k;
  int max = dimension(g);
  cout << endl << " \t ";
  for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
  cout << endl;
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1 */
  for(i = 0; i < max; i = i+1) {
    cout << "\t|";
    for(j=0; j < max; j=j+1) {
      if(g.table.at(i).at(j) == 0) {
	      cout << "      |";
      } else { cout << " " << setw(4) << g.table.at(i).at(j) << " |" ; }
    }
    if (i != max-1) {
      cout << endl << "\t|";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << "|" << endl;
    } else {
      cout << endl << "\t ";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << endl;
    }
  }
  cout << endl << "Score: " << score(g) << ", Vides: " << vides(g) << endl;
}
