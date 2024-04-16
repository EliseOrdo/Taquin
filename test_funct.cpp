#include "jeu.h"
#include "jeu.cpp"
#include <cassert>

void test_vides(){
    Grille g1, g2, g3, g4;
    g1.table = {{}};
    g2.table = {{1, 2}, {0}};
    g3.table = {{1, 2, 0, 5,7}, {0, 6, 8, 9, 3}, {0, 0, 0, 0, 0}, {1, 0, 9, 4, 12}, {252, 0, 32, 54, 0}};
    g4.table = {{1, 2, 10, 5,7}, {10, 6, 8, 9, 3}, {10, 10, 10, 10, 10}, {1, 10, 9, 4, 12}, {252, 10, 32, 54, 10}};
    assert(vides(g1) == -1);
    assert(vides(g2) == -1);
    assert(vides(g3) == 10);
    assert(vides(g4) == 0);

}

void vect(Grille g){
    for(size_t i = 0; i<g.dimension ; i++){
        for(size_t j = 0; j<g.dimension; j++){
            cout<<"  "<<g.table.at(i).at(j);
        }cout<<endl;
    }
}

int main(){
    resetRand(true);
    test_vides();
    Grille g;
    init(g, 4, 2048, 5);
    affiche(g);
    droite(g);
    affiche(g);
    gauche(g);
    affiche(g);
    haut(g);
    affiche(g);
    bas(g);
    affiche(g);
    return 0;
}