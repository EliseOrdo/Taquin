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
  int res = -1;
  return res;
  }

int score(const Grille &g){
  int res = -1;
  return res;
  }

bool succes(const Grille &g) { return false; }

bool init(Grille &g, int dimension, int cible, int proportion) {
  bool res = false;
  // a faire
  return res;
}

// Ne pas oublier de vérifier la validité des paramètres !
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion) {
  size_t dim = v.size(); bool res = false;
  if (dim < 4) {
    cerr << "Nombre de lignes insuffisant: " << v.size() << endl;
    return res;
  }
  // a faire
  return res;
}


int droite(Grille &g){
  for(size_t i=0; i<g.table.size(); i+=1){
    for(size_t j=g.table.size()-1; j>0; j-=1){ //voir consigne, on parcours dans l'autre sens pour fusionner à partir de la droite
      if(g.table.at(i).at(j) == g.table.at(i).at(j-1)){
        // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(i).at(j) += g.table.at(i).at(j) ; 
        g.table.at(i).at(j-1) += 0; //on vide le case de gauche
      }
      else if (g.table.at(i).at(j-1) != 0 and g.table.at(i).at(j)==0 ){
        //si la case de droite est libre et que celle de gauche est pleine, on décale celle de gauche à droite
        g.table.at(i).at(j) = g.table.at(i).at(j-1);
        g.table.at(i).at(j-1) = 0;
      }
    } 
  }//rajouter 2 cases de 2 si l'action a été possible
  return vides(g); // ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
  }

int gauche(Grille &g)
{ int res = -1;
return vides(g);
}

int haut(Grille &g){
  int res = -1;
  return vides(g);
  }

int bas(Grille &g){
  int res = -1;
  return vides(g);
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
