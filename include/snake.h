#ifndef SNAKE_H

    #define SNAKE_H

    #include <raylib.h>
    #include "config.h"


    typedef struct {

        Rectangle corp;

    } CaseSnake;

    CaseSnake *ajouteCaseSnake(CaseSnake *tete, int *tailleSnake);
    CaseSnake *mouvementSerpent(CaseSnake *tete, int *tailleSnake, int dx, int dy);

#endif
