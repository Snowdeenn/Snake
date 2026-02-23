#include "../include/jeu.h"
#include "../include/config.h"
#include "../include/snake.h"
#include "../include/pomme.h"



int collisionSerpentMurs(CaseSnake *tete) {

    int gameOver = 0;

// Verifie si le serpent sort de la grill
     if(tete->corp.x < SIZE_MIN_FENETRE || tete->corp.y < SIZE_MIN_FENETRE || tete->corp.x >= LARGEUR_FENETRE || tete->corp.y >= LONGUEUR_FENETRE) {
        gameOver = 1;
     }

    return gameOver;
}

int collisionSerpentLuiMeme(CaseSnake *tete, int taille) {

    int gameOver = 0;

//  On regarde si la tete mord le corp
    for(int i = 1; i < taille; i++) {
        if(CheckCollisionRecs((*tete).corp, ((tete) + i)->corp)) {
            gameOver = 1;
        }
    }

    return gameOver;
}

int collisionSerpentPomme(CaseSnake *tete, Pomme pomme) {

    int mangePomme = 0;

// on regarde si le serpent mange une pomme
    if(CheckCollisionRecs((*tete).corp, pomme.casePomme)) {
        mangePomme = 1;
    }

    return mangePomme;
}