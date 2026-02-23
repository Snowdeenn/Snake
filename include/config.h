// config.h
#ifndef CONFIG_H
#define CONFIG_H

#define TAILLE_CASE 20
#define SIZE_MIN_FENETRE 0
#define LARGEUR_FENETRE 1040
#define LONGUEUR_FENETRE 1880

#include <raylib.h>
typedef enum {

    HAUT = KEY_W,
    BAS = KEY_S,
    DROITE = KEY_D,
    GAUCHE = KEY_A

} Touche;

#endif