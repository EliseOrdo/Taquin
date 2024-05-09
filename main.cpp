#include "jeu.h"
#include "jeu.cpp"
#include <cassert>

int main(){
  Grille g;
  cout<<"Bienvenue dans le 2048 "<<endl<<"z : haut  q: gauche s: bas  d: droite"<<endl;
  resetRand(true);
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