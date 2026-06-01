#ifndef JEU_H

    #define JEU_H


    #include "../include/config.h"
    #include "../include/snake.h"
    #include "../include/pomme.h"

    int collisionSerpentMurs(CaseSnake *tete);           // game over si hors grille
    int collisionSerpentLuiMeme(CaseSnake *tete, int taille); // game over si mord sa queue
    int collisionSerpentPomme(CaseSnake *tete, Pomme pomme);  // mange la pomme

#endif