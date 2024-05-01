#include "jeu.h"
#include "jeu.cpp"
#include <cassert>

void test_dimension(){
    cout << "Debut du test de dimension()" << endl;
    Grille g1, g2, g3, g4, g5;
    g1.table = {};
    g2.table = {{}};
    g3.table = {{1}};
    g4.table = {{1,4,8,16}, {0, 2, 6, 9}};
    g5.table = {{0, 1, 2, 4, 8}, {16, 32, 64, 128, 256}, {0, 0, 0, 0, 0}, {0, 1, 2, 4, 8}, {16, 32, 64, 128, 256},};
    assert(dimension({{}}) == -1);
    assert(dimension({}) == -1);
    assert(dimension(g3) == 1);
    assert(dimension(g4) == -1);
    assert(dimension(g5) == 5);
    cout << "Fin du test de dimension()" << endl << endl;
}

void test_init(){
    cout << "Debut du test de init()" << endl;
    //resetRand(true);
    Grille g;
    init(g, 4, 2048, 5);
    affiche(g);
    cout << "Fin du test de init()" << endl << endl;
}

void test_vides(){
    cout << "Debut du test de vides()" << endl;
    Grille g1, g2, g3, g4;
    g1.table = {{}};
    g2.table = {{1, 2}, {0}};
    g3.table = {{1, 2, 0, 5,7}, {0, 6, 8, 9, 3}, {0, 0, 0, 0, 0}, {1, 0, 9, 4, 12}, {252, 0, 32, 54, 0}};
    g4.table = {{1, 2, 10, 5,7}, {10, 6, 8, 9, 3}, {10, 10, 10, 10, 10}, {1, 10, 9, 4, 12}, {252, 10, 32, 54, 10}};
    assert(vides(g1) == -1);
    assert(vides(g2) == -1);
    assert(vides(g3) == 10);
    assert(vides(g4) == 0);
    cout << "Fin du test de vides()" << endl << endl;
}

void test_mouvements(){
    cout<<"Debut du test des mouvements"<<endl;
    Grille g;
    init(g, 4, 2048, 5);
    cout<<"nouvelle grille :"<<endl;
    affiche(g);
    cout<<"droite :"<<endl;
    droite(g);
    affiche(g);
    cout<<"gauche :"<<endl;
    gauche(g);
    affiche(g);
    cout<<"haut :"<<endl;
    haut(g);
    affiche(g);
    cout<<"bas :"<<endl;
    bas(g);
    affiche(g);
     cout<<"droite :"<<endl;
    droite(g);
    affiche(g);
    cout<<"gauche :"<<endl;
    gauche(g);
    affiche(g);
    cout<<"haut :"<<endl;
    haut(g);
    affiche(g);
    cout<<"bas :"<<endl;
    bas(g);
    affiche(g);
    cout<<"Fin du test des mouvements"<<endl;
}

void test_proportion(){
    cout << "Debut du test de proportion()" << endl;
    Grille g1, g2, g3, g4, g5;
    g1.table = {{0, 2, 0, 2}, {0, 2, 0, 2}, {0, 2, 0, 2}, {0, 2, 0, 2}};
    g2.table = {};
    g3.table = {{}};
    g4.table = {{1}, {}};
    g5.table = {{2, 0, 4, 8}, {8, 16, 2, 0}, {64, 32, 2, 0}, {128, 2, 0, 0}};
    assert(proportion(g1) == 5);
    assert(proportion(g2) == -1);
    assert(proportion(g3) == -1);
    assert(proportion(g4) == -1);
    assert(proportion(g5) == 2);
    cout << "Fin du test de proportion()" << endl;
}

void test_succes(){
    cout<<"debut du test de succes"<<endl;
    Grille g;
    init(g,4,4,5);
    assert(succes(g) == true);
    Grille d;
    init(d,4,5,3);
    assert(succes(d) == false);
    cout<<"fin du test de succes"<<endl;
}

int main(){
    test_dimension();
    test_init();
    test_vides();
    test_proportion();
    test_mouvements();
    //test_succes();
    return 0;
}