#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/pomme.h"
#include "../include/config.h"
#include "../include/snake.h"
#include "../include/jeu.h"

int main(void) {

    InitWindow(LONGUEUR_FENETRE, LARGEUR_FENETRE, "Snake.exe");
    SetTargetFPS(60);
    srand(time(NULL));
    

    CaseSnake *teteSnake = malloc(sizeof(CaseSnake));

    if(teteSnake == NULL) {

        fprintf(stderr, "Erreur lors de l'allocation mémoire du serpent");
        return EXIT_FAILURE;

    }

   
    // Aligné sur la grille
    teteSnake->corp.x = (LONGUEUR_FENETRE / 2 / TAILLE_CASE) * TAILLE_CASE;
    teteSnake->corp.y = (LARGEUR_FENETRE / 2 / TAILLE_CASE) * TAILLE_CASE;

    teteSnake->corp.width = TAILLE_CASE;
    teteSnake->corp.height = TAILLE_CASE;


    int tailleSnake = 1;
    int nombrePomme = 0;

    Pomme pomme = creerPomme();

    float timer = 0;
    float vitesse = 0.15f;  // 1 mouvement toutes les 0.1 secondes

    int gameOver = 0;

    // Stocke la direction courante
    int dx = 1, dy = 0;  // démarre vers la droite

    while(!WindowShouldClose()) {

    float dt = GetFrameTime();
    timer += dt;

    // Dans la boucle — change juste la direction
    if(IsKeyPressed(DROITE) && dx != 1) { dx = 1;  dy = 0; }
    if(IsKeyPressed(GAUCHE) && dx != -1)  { dx = -1; dy = 0; }
    if(IsKeyPressed(BAS)    && dy != 1) { dx = 0;  dy = 1; }
    if(IsKeyPressed(HAUT)   && dy != -1)  { dx = 0;  dy = -1; }

    if(!gameOver) {
        // Mouvement automatique selon le timer
        if(timer >= vitesse) {

            teteSnake = mouvementSerpent(teteSnake, &tailleSnake, dx, dy);
            timer = 0;
        }

        if(collisionSerpentLuiMeme(teteSnake, tailleSnake) != 0 || collisionSerpentMurs(teteSnake) != 0) {
            gameOver = 1;
        }

        if(collisionSerpentPomme(teteSnake, pomme) != 0) {

            pomme = creerPomme();
            teteSnake = ajouteCaseSnake(teteSnake, &tailleSnake);
            nombrePomme++;

        }

    }

    BeginDrawing();
        ClearBackground(BLACK);

        if(gameOver) {
            
            const char * texteGO = TextFormat("Gamer Over !!");

            DrawText(texteGO, GetScreenWidth() / 2 - MeasureText(texteGO, 40) / 2, 300, 40, WHITE);

        } else {

            for(int i = 0; i < tailleSnake; i++) {
                DrawRectangleRec((teteSnake + i)->corp, BLUE);
            }

            DrawRectangleRec(pomme.casePomme, PINK);
        }

        DrawText(TextFormat("Pomme : %d", nombrePomme), 50, 50, 30, WHITE);
    EndDrawing();
    }

    return EXIT_SUCCESS;
}