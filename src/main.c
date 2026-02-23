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

   
    // Aligné sur la grille
    teteSnake->corp.x = (LONGUEUR_FENETRE / 2 / TAILLE_CASE) * TAILLE_CASE;
    teteSnake->corp.y = (LARGEUR_FENETRE / 2 / TAILLE_CASE) * TAILLE_CASE;

    teteSnake->corp.width = TAILLE_CASE;
    teteSnake->corp.height = TAILLE_CASE;


    int tailleSnake = 1;

    Pomme pomme = creerPomme();

    float timer = 0;
    float vitesse = 0.1f;  // 1 mouvement toutes les 0.1 secondes

    int gameOver = 0;

    while(!WindowShouldClose()) {

    float dt = GetFrameTime();
    timer += dt;

    // Stocke la direction courante
    int dx = 1, dy = 0;  // démarre vers la droite

    // Dans la boucle — change juste la direction
    if(IsKeyDown(DROITE) && dx != 1) { dx = 1;  dy = 0; }
    if(IsKeyDown(GAUCHE) && dx != -1)  { dx = -1; dy = 0; }
    if(IsKeyDown(BAS)    && dy != 1) { dx = 0;  dy = 1; }
    if(IsKeyDown(HAUT)   && dy != -1)  { dx = 0;  dy = -1; }

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

        }

    }

    BeginDrawing();
        ClearBackground(BLACK);

        if(gameOver) {
            
            const char * texteGO = TextFormat("Gamer Over !!");

            DrawText(texteGO, GetScreenWidth() / 2 - MeasureText(texteGO, 40) / 2, 480, 40, WHITE);

        } else {

            for(int i = 0; i < tailleSnake; i++) {
                DrawRectangleRec((teteSnake + i)->corp, BLUE);
            }

            DrawRectangleRec(pomme.casePomme, PINK);
        }

        for(int i = 0; i < tailleSnake; i++) {
            DrawText(TextFormat("seg%d : %.0f - %.0f", i, (teteSnake + i)->corp.x, (teteSnake + i)->corp.y), 10, 20 * i + 200, 20, WHITE);
        }
        DrawText(TextFormat("collision : %d", collisionSerpentMurs(teteSnake)), 10, 150, 20, RED);
        DrawText(TextFormat("%d - %d", (int)pomme.casePomme.x, (int)pomme.casePomme.y), 100, 100, 30, WHITE);
    EndDrawing();
    }

    return EXIT_SUCCESS;
}