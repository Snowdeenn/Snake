#include "../include/pomme.h"
#include <stdio.h>
#include <stdlib.h>


Pomme creerPomme() {

    int x = (GetRandomValue(0, LONGUEUR_FENETRE / TAILLE_CASE - 1) * TAILLE_CASE);
    int y = (GetRandomValue(0, LARGEUR_FENETRE / TAILLE_CASE - 1) * TAILLE_CASE);

    Pomme pomme;

    pomme.casePomme.x = x;
    pomme.casePomme.y = y;
    pomme.casePomme.width = TAILLE_CASE;
    pomme.casePomme.height = TAILLE_CASE;

    return pomme;

}