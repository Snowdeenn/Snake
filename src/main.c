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
    

    CaseSnake *teteSnake = malloc(sizeof(CaseSnake));

    if(teteSnake == NULL) {

        fprintf(stderr, "Erreur lors de l'allocation mémoire du serpent");
        return EXIT_FAILURE;

    }

   
    teteSnake->corp.x = LONGUEUR_FENETRE / 2;
    teteSnake->corp.y = LARGEUR_FENETRE / 2;
    teteSnake->corp.width = TAILLE_CASE;
    teteSnake->corp.height = TAILLE_CASE;


    int tailleSnake = 1;
    Pomme pomme = creerPomme();
    float timer = 0;
    float vitesse = 0.1f;  // 1 mouvement toutes les 0.1 secondes

    while(!WindowShouldClose()) {

        float dt = GetFrameTime();
        timer += dt;

        if(IsKeyDown(DROITE)) {
            if(timer >= vitesse) {
                teteSnake = mouvementSerpent(teteSnake, &tailleSnake, 1, 0);
                    timer = 0;
                }
        }

        if(IsKeyDown(GAUCHE)) {
             if(timer >= vitesse) {
                teteSnake = mouvementSerpent(teteSnake, &tailleSnake, -1, 0);
                    timer = 0;
                }
        }       

        if(IsKeyDown(BAS)) {
            if(timer >= vitesse) {
                teteSnake = mouvementSerpent(teteSnake, &tailleSnake, 0, 1);
                    timer = 0;
                }
        }

        if(IsKeyDown(HAUT)) {
            if(timer >= vitesse) {
                teteSnake = mouvementSerpent(teteSnake, &tailleSnake, 0, -1);
                    timer = 0;
                }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            for(int i = 0; i < tailleSnake; i++) {
                DrawRectangleRec((teteSnake + i)->corp, BLUE);
            }

            DrawRectangleRec(pomme.casePomme, PINK);
            if(collisionSerpentPomme(teteSnake, pomme) != 0) {

                pomme = creerPomme();
                teteSnake = ajouteCaseSnake(teteSnake, &tailleSnake);

            }
                
            DrawText(TextFormat("%d - %d", (int)pomme.casePomme.x, (int)pomme.casePomme.y), 100, 100, 30, WHITE);
        EndDrawing();
}

    return EXIT_SUCCESS;
}