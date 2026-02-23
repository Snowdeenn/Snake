#include "../include/snake.h"
#include <stdio.h>
#include <stdlib.h>

CaseSnake *ajouteCaseSnake(CaseSnake *tete, int *tailleSnake) {
 
    
//  Suit la taille du serpent
    (*tailleSnake)++;

//  Alloue la mémoire pour la nouvelle case
    CaseSnake *caseTmp = realloc(tete, (*tailleSnake) * sizeof(CaseSnake));

    if(caseTmp == NULL) {

        free(tete);
        exit(EXIT_FAILURE);

    }

    tete = caseTmp;

    int derniereCase = (*tailleSnake) - 1;

// Ajoute la nouvelle Case à la fin du Snake
    (tete + derniereCase)->corp.x = (tete + derniereCase - 1)->corp.x;
    (tete + derniereCase)->corp.y = (tete + derniereCase - 1)->corp.y;

    printf("%d", (*tailleSnake));

    return tete;
}

CaseSnake *mouvementSerpent(CaseSnake *tete, int *tailleSnake, int dx, int dy) {

//  Décaler tous les segments de la fin vers le début
    for(int i = (*tailleSnake) - 1; i > 0; i--) {
        (tete + i)->corp = (tete + i - 1)->corp;
    }

//  Déplacer la tête selon la direction
    tete->corp.x += dx * TAILLE_CASE;
    tete->corp.y += dy * TAILLE_CASE;


    return tete;

}
