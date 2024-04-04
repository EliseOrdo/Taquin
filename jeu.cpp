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
  int res = -1; //si aucun changement possible
  for(size_t i=0; i<g.table.size(); i+=1){
    size_t id1 = g.table.size()-1; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //voir consigne, on parcours dans l'autre sens pour fusionner à partir de la droite
    int val1 = g.table.at(i).at(id1); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    size_t id2 = id1 -1 ;
    while(id2 >= 0){ //tant qu'on est pas au début de la ligne
      val2 = g.table.at(i).at(id2);
      if(val2 == 0){
        id2 -= 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(i).at(id1) = val2;
        g.table.at(i).at(id2) = 0;
        id2 -= 1;
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(i).at(id1) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(i).at(id2) = 0; //et on vide la case de gauche ( à faire avant chgmt id1 pour éviter chevauchement)
        //une case fusionnée ne peut se refusionner dans le même mouvement
        id1 -= 1;
        val1 = g.table.at(i).at(id1);
        id2 -= 1;
        //on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else{
        id1 -= 1;
        val1 = g.table.at(i).at(id1);
        if(id1 == id2){id2-=1;} //on évite que les indices se chevauchent
      }
      
    } 
  }//rajouter une tuile de 2 ou 4 si l'action a été possible
  if(res!=-1){

    res = vides(g);
  }
  return res; // vides(g) ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
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
