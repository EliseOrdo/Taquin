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
  return g.score;
}

bool succes(const Grille &g) { 
  for(size_t i=0; i<dimension(g); i+=1 ){
    for(size_t j=0; j<dimension(g); j+=1){
      if(g.table.at(i).at(j) == cible(g)){return true;}
    }
  }
  return false; 
}

void ajoute(Grille &g){
  /*ajoute une nouvelle case (hasard) dans la grille g*/
  //parcours de la grille pour trouver le truc donné par place()
  int id = -1; // numéro de case vide où on est
  int pla = place(g);
  int dim = dimension(g);
  for(size_t i = 0; i<dim; i+=1){
    for(size_t j = 0; j<dim; j+=1){
      if(g.table.at(i).at(j) == 0){ //si la case est vide, on incrémente l'indice
        id += 1; }
      if(id == pla){
        g.table.at(i).at(j) = nouvelle(g);//(nouvelle donne la valeur de la tuile) ; si on est sur la i-ème place, on met la valeur
        i = dim;
        j=dim;//on force la sortie
        }
    }
  }
}

bool init(Grille &g, int dimension, int cible, int proportion) {
  /*initialise g avec les parametres indiques ; 
  En sortie, g doit comporter deux tuiles dont les
  valeurs et positions sont obtenues par des appels aux fonctions nouvelle et place decrites ci-apres 
  la fonction renvoie true en cas de succes et false sinon */
  g.proportion = proportion;
  g.cible = cible;
  g.score = 0;
  bool res = false;
  if(dimension <= 0){return false;}
  //parcours de la grille pour trouver le truc donné par place()
  vector<int> t = vector<int> (dimension,0);
  g.table = vector<vector<int>> (dimension, t);
  int id = 0; // numéro de case vide où on est
  int pla = place(g);
  for(size_t i = 0; i<dimension; i+=1){
    for(size_t j = 0; j<dimension; j+=1){
      t.at(j) = 0; //initialisation de la case à 0
      if(id == pla){t.at(j) = nouvelle(g);} //(nouvelle donne la valeur de la tuile) ; si on est sur la i-ème place (forcément vide car initialisation), on met la valeur
      id += 1; 
    }g.table.at(i) = t;
  }ajoute(g); //on ajoute la 2e tuile de départ
  res = true; 

  return res;
}

bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion){
  size_t dim = dimension(g);
  // Verification de la validite des parametres
  if(dim < 4){
    return -1;
  }
  //Initialisation de la grille
  g.proportion = proportion;
  g.cible = cible;
  g.score = 0;
  g.table = v;
  return true;
}

int droite(Grille &g){
  int res = -1; //si aucun changement possible
  int dim = dimension(g);
  if (dim <= 0){return -1;}
  for(size_t i=0; i<g.table.size(); i+=1){
    int id1 = g.table.size()-1; //comme c'est carré l'indice de fin est le même pour lignes et colonnes
    //voir consigne, on parcours dans l'autre sens pour fusionner à partir de la droite
    int val1 = g.table.at(i).at(id1); //on garde le chiffre en mémoire pour l'ajouter
    int val2 = 0; 
    int id2 = id1 -1 ;
    while(id2 >= 0){ //tant qu'on est pas au début de la ligne
      val2 = g.table.at(i).at(id2);
      cout<<"val2 : "<<val2<<" ligne : "<<id2<<" colonne : "<<i<<endl;
      if(val2 == 0){
        id2 -= 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(i).at(id1) = val2;
        g.table.at(i).at(id2) = 0;
        id2 -= 1;
        val1 = g.table.at(i).at(id1);
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(i).at(id1) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.table.at(i).at(id2) = 0; //et on vide la case de gauche ( à faire avant chgmt id1 pour éviter chevauchement)
        g.score += g.table.at(i).at(id1);
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
    ajoute(g);
    res = vides(g);
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
        val1 = g.table.at(i).at(id1);
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(i).at(id1) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.score += g.table.at(i).at(id1);
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
    ajoute(g);
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
      cout<<"val2 : "<<val2<<" ligne : "<<id2<<" colonne : "<<i<<endl;
      if(val2 == 0){
        id2 += 1;
      }
      else if(val1 == 0 and val2 != 0){
        g.table.at(id1).at(i) = val2;
        g.table.at(id2).at(i) = 0;
        id2 += 1;
        val1 = g.table.at(id1).at(i);
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        cout<<"val1==val2 == "<<val1;
        g.table.at(id1).at(i) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.score += g.table.at(id1).at(i);
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
    ajoute(g);
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
        val1 = g.table.at(id1).at(i);
        //si on déplace un truc, on a pu faire le mouvement, on refresh res
        res = 1;
      }
      else if(val1 == val2){
        g.table.at(id1).at(i) = val1 + val2; // si les cases adjacentes ont les mêmes valeurs, on les fusionne (somme)
        g.score += g.table.at(id1).at(i);
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
    ajoute(g);
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

bool perdu(Grille &g){
  /* renvoie true quand la grille est pleine et que y plus de mouvement possible*/
  if (vides(g) != 0){
    return false;
  }
  int dim = dimension(g);
  for (size_t i = 0; i < dim - 1; i +=1 ){
    for (size_t j = 0; j < dim -1; j += 1){
      /*Cas d'un mouvement horizontal possible*/
      if (g.table.at(i).at(j) == g.table.at(i).at(j+1)){
        return false;
      }
      /*Cas d'un mouvement vertical possible*/
      if (g.table.at(i).at(j) == g.table.at(i+1).at(j)){
        return false;
      }
    }
  }
  return true;

int main(){
  Grille g;
  cout<<"Bienvenue dans le 2048"<<endl<<"z : haut  q: gauche s: bas  d: droite"<<endl;
  init(g,4, 2048, 4);
  affiche(g);
  bool suite = true;
  char mouv;
  do{
    
    cout<<"Quel mouvement voulez-vous effectuer ?"<<endl;
    cin>>mouv;
    if(mouv== 'z'){haut(g);}
    if(mouv== 'q'){gauche(g);}
    if(mouv== 's'){bas(g);}
    if(mouv== 'd'){droite(g);}
    else{cout<<"veuillez entrer z,q,s ou d."<<endl;}
    affiche(g);
    if(succes(g)){
      suite = false;
      cout<<"félicitations !!"<<endl;
    }
    if(perdu(g)){
        suite = false;
        cout<<"Fin"<<endl;
    }
  }while(suite);
  return 0;
}