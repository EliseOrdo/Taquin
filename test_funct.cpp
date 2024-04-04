#include "jeu.h"
#include <cassert>
#include "jeu.cpp"

int main(){
    Grille g;
    init(g, 4, 2048, 5);
    affiche(g);
    return 0;
}