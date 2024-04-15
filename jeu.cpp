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
  assert(dimension > 0);
  g.dimension = dimension;
  g.cible = cible;
  g.proportion = proportion;
  //parcours de la grille pour trouver le truc donné par place()
  int id = 0; // numéro de case vide où on est
  vector<int> t = vector<int> (dimension,0);
  g.table = vector<vector<int>> (dimension, t);
  int pla = place(g);
  for(size_t i = 0; i<dimension; i+=1){
    for(size_t j = 0; j<dimension; j+=1){
      t.at(j) = 0; //initialisation de la case à 0
      if(id == pla){t.at(j) = nouvelle(g);} //(nouvelle donne la valeur de la tuile) ; si on est sur la i-ème place (forcément vide car initialisation), on met la valeur
      id += 1; 
    }g.table.at(i) = t;
  }
  res = true; 

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
    int id1 = g.table.size()-1; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //voir consigne, on parcours dans l'autre sens pour fusionner à partir de la droite
    cout<<"id1: "<<id1<<endl;
    int val1 = g.table.at(i).at(id1); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    int id2 = id1 -1 ;
    while(id2 >= 0){ //tant qu'on est pas au début de la ligne
      cout<<"début while "<< i <<endl;
      val2 = g.table.at(i).at(id2); //là
      cout<<"id2 :"<<id2<<" val2: "<<val2<<" val1: "<<val1<<endl;
      if(val2 == 0){
        cout<<"val2 == 0"<<endl;
        id2 -= 1;
        cout<<"id2 bis: "<<id2<<endl;
      }
      else if(val1 == 0 and val2 != 0){
        cout<<"ligne "<<i<<" colonne "<< id1 << "valeur : "<< val2 <<endl;
        g.table.at(i).at(id1) = val2;
        cout << "fait : "<<g.table.at(i).at(id1)<<endl;
        g.table.at(i).at(id2) = 0;
        id2 -= 1;
        val1 = g.table.at(i).at(id1);
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        cout<<"val1 == val2"<<endl;
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
        cout<<"else"<<endl;
        id1 -= 1;
        val1 = g.table.at(i).at(id1);
        if(id1 == id2){id2-=1;} //on évite que les indices se chevauchent
      }
    } 
  }//rajouter une tuile de 2 ou 4 si l'action a été possible
  if(res!=-1){
    //parcours de la grille pour trouver le truc donné par place()
    int id = 0; // numéro de case vide où on est
    int pla = place(g);
    for(size_t i = 0; i<g.dimension; i+=1){
      for(size_t j = 0; j<g.dimension; j+=1){
        g.table.at(i).at(j) = 0; //initialisation de la case à 0
        if(id == pla){g.table.at(i).at(j) = nouvelle(g);} //(nouvelle donne la valeur de la tuile) ; si on est sur la i-ème place (forcément vide car initialisation), on met la valeur
        id += 1; 
      }
    res = vides(g);
  }
  }
  return res; // vides(g) ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
  }

int gauche(Grille &g)
{ int res = -1; //si aucun changement possible
  for(size_t i=0; i<g.table.size(); i+=1){
    int id1 = 0; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //gauche
    int val1 = g.table.at(i).at(id1); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    int id2 = id1 +1 ;
    while(id2 < g.table.size()){ //tant qu'on est pas à la fin de la ligne
      val2 = g.table.at(i).at(id2);
      if(val2 == 0){
        id2 += 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(i).at(id1) = val2;
        g.table.at(i).at(id2) = 0;
        id2 += 1;
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(i).at(id1) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(i).at(id2) = 0; //et on vide la case de gauche ( à faire avant chgmt id1 pour éviter chevauchement)
        //une case fusionnée ne peut se refusionner dans le même mouvement
        id1 += 1;
        val1 = g.table.at(i).at(id1);
        id2 += 1;
        //on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else{
        id1 += 1;
        val1 = g.table.at(i).at(id1);
        if(id1 == id2){id2+=1;} //on évite que les indices se chevauchent
      }
      
    } 
  }//rajouter une tuile de 2 ou 4 si l'action a été possible
  if(res!=-1){

    res = vides(g);
  }
  return res; // vides(g) ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
}

int haut(Grille &g){
  int res = -1; //si aucun changement possible
  for(size_t i=0; i<g.table.size(); i+=1){
    int id1 = 0; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //voir consigne, on parcours dans l'autre sens pour fusionner à partir du haut
    int val1 = g.table.at(id1).at(i); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    int id2 = id1 +1 ;
    while(id2 < g.table.size()){ //tant qu'on est pas au début de la ligne
      val2 = g.table.at(id2).at(i);
      if(val2 == 0){
        id2 += 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(id1).at(i) = val2;
        g.table.at(id2).at(i) = 0;
        id2 += 1;
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(id1).at(i) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(id2).at(i) = 0; //et on vide la case de gauche ( à faire avant chgmt id1 pour éviter chevauchement)
        //une case fusionnée ne peut se refusionner dans le même mouvement
        id1 += 1;
        val1 = g.table.at(id1).at(i);
        id2 += 1;
        //on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else{
        id1 += 1;
        val1 = g.table.at(id1).at(i);
        if(id1 == id2){id2+=1;} //on évite que les indices se chevauchent
      }
      
    } 
  }//rajouter une tuile de 2 ou 4 si l'action a été possible
  if(res!=-1){

    res = vides(g);
  }
  return res; // vides(g) ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
  }

int bas(Grille &g){
  int res = -1; //si aucun changement possible
  for(size_t i=0; i<g.table.size(); i+=1){
    int id1 = g.table.size() - 1; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //gauche
    int val1 = g.table.at(id1).at(i); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    int id2 = id1 -1 ;
    while(id2 >= 0){ //tant qu'on est pas au début de la colonne
      val2 = g.table.at(id2).at(i);
      if(val2 == 0){
        id2 -= 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(id1).at(i) = val2;
        g.table.at(id2).at(i) = 0;
        id2 -= 1;
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(id1).at(i) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(id2).at(i) = 0; //et on vide la case de gauche ( à faire avant chgmt id1 pour éviter chevauchement)
        //une case fusionnée ne peut se refusionner dans le même mouvement
        id1 -= 1;
        val1 = g.table.at(id1).at(i);
        id2 -= 1;
        //on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else{
        id1 -= 1;
        val1 = g.table.at(id1).at(i);
        if(id1 == id2){id2-=1;} //on évite que les indices se chevauchent
      }
      
    } 
  }//rajouter une tuile de 2 ou 4 si l'action a été possible
  if(res!=-1){

    res = vides(g);
  }
  return res; // vides(g) ou -1 si l'action est impossible mais je sais pas quand est-ce que c'est impossible
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
