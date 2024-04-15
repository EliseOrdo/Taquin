#include "jeu.h"
#include <iomanip> // pour setw dans affichage.
#include "dispo.cpp"

/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g){
  int res = 0;
  /*Regarde si c'est pas une grille vide*/
  if (g.table.size() == 0){
    return -1;
  }
  for (size_t i=0; i < g.table.size(); i+=1){
    if (g.table.size() != g.table.at(i).size()){
        return -1;
      }
    for (size_t j=0; j < g.table.at(i).size(); j+=1){
      if (g.table.at(i).at(j) == 0){
        res += 1;
      }
    }
  }
  return res;
}

int proportion(const Grille &g){
  return g.proportion;
  }

int cible(const Grille &g){
  return g.cible;
  }

int dimension(const Grille &g){
  return g.dimension;
  }

int score(const Grille &g){
  int res = -1;
  return res;
  }

bool succes(const Grille &g) { return false; }

bool init(Grille &g, int dimension, int cible, int proportion) {
  /*initialise g avec les parametres indiques ; 
  En sortie, g doit comporter deux tuiles dont les
  valeurs et positions sont obtenues par des appels aux fonctions nouvelle et place decrites ci-apres 
  la fonction renvoie true en cas de succes et false sinon */
  bool res = false;
  g.dimension = dimension;
  g.cible = cible;
  g.proportion = proportion;
  //parcours de la grille pour trouver le truc donné par place()
  int pla = place(g);
  int id = 0; // numéro de case vide où on est
  for(size_t i = 0; i<dimension; i+=1){
    for(size_t j = 0; j<dimension; j+=1){
      g.table.at(i).at(j) = 0; //initialisation de la case à 0
      if(id == pla){g.table.at(i).at(j) = nouvelle(g);} //(nouvelle donne la valeur de la tuile) ; si on est sur la i-ème place (forcément vide car initialisation), on met la valeur
      id += 1; 
    }
  }res = true; 

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
