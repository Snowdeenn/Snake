#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/pomme.h"
#include "../include/config.h"
#include "../include/snake.h"
#include "../include/jeu.h"

int main(void) {

    InitWindow(LONGUEUR_FENETRE, LARGEUR_FENETRE, "Snake.exe");
    srand(time(NULL));

    Pomme pomme = creerPomme();

    while(!WindowShouldClose()) {



    BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("%d - %d", (int)pomme.casePomme.x, (int)pomme.casePomme.y), 100, 100, 30, WHITE);
    EndDrawing();
}

    return EXIT_SUCCESS;
}