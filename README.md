# Snake — C & Raylib

Un Snake classique en C avec la bibliothèque **Raylib**, avec gestion de la mémoire dynamique et détection de collisions.

---

## Table des matières

- [Aperçu](#aperçu)
- [Structure des fichiers](#structure-des-fichiers)
- [Compilation avec CMake](#compilation-avec-cmake)
- [Fonctionnement du jeu](#fonctionnement-du-jeu)
- [Architecture du code](#architecture-du-code)
- [Constantes configurables](#constantes-configurables)

---

## Aperçu

- Fenêtre 900×600 pixels, grille de cases de 20px
- Déplacement automatique cadencé par un timer (indépendant des FPS)
- Pommes générées aléatoirement sur la grille
- Game over sur collision avec les murs ou avec le corps du serpent
- Compteur de pommes mangées affiché en temps réel

---

## Structure des fichiers

```
Snake/             
├── include/
│   ├── config.h        # Constantes globales et enum des touches
│   ├── snake.h         # Structure CaseSnake, déclarations mouvement
│   ├── pomme.h         # Structure Pomme, déclaration création
│   └── jeu.h           # Déclarations des fonctions de collision
└── src/
    ├── snake.c         # Mouvement et agrandissement du serpent
    ├── pomme.c         # Génération aléatoire d'une pomme
    └── jeu.c           # Logique des collisions
    └── main.c          # Boucle principale, initialisation, rendu
```

---

## Compilation avec CMake

### Prérequis

- CMake 3.14+
- Raylib installé sur le système (ou via FetchContent)

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.14)
project(Snake C)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(Snake
    main.c
    src/snake.c
    src/pomme.c
    src/jeu.c
)

target_include_directories(Snake PRIVATE include)
target_link_libraries(Snake PRIVATE raylib)
```

### Compilation

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

---

## Fonctionnement du jeu

| Action | Touche |
|---|---|
| Aller à droite | `D` |
| Aller à gauche | `A` |
| Aller en bas | `S` |
| Aller en haut | `W` |
| Quitter | `Échap` / fermer la fenêtre |

Le serpent se déplace automatiquement toutes les **0.15 secondes**. Manger une pomme allonge le serpent d'une case et en génère une nouvelle aléatoirement. Le jeu s'arrête sur collision avec un mur ou avec le corps du serpent.

---

## Architecture du code

### Représentation du serpent

Le serpent est un **tableau dynamique** de `CaseSnake` alloué sur le tas avec `malloc` / `realloc`. Le pointeur `teteSnake` pointe toujours vers la case d'index 0 (la tête). Les segments suivants sont accessibles par arithmétique de pointeurs : `(teteSnake + i)`.

```
teteSnake[0]  →  tête
teteSnake[1]  →  segment 1
teteSnake[2]  →  segment 2
...
```

### Mouvement

À chaque tick (toutes les 0.15s), `mouvementSerpent` décale tous les segments de la fin vers le début — chaque segment prend la position du précédent — puis déplace la tête selon `dx` / `dy`. C'est équivalent à une file sans en avoir le coût d'allocation.

### Détection de collisions

Toutes les collisions utilisent `CheckCollisionRecs` de Raylib (AABB) :

- **Murs** — vérifie si la position de la tête sort des bornes de la fenêtre
- **Corps** — compare la tête avec chacun des segments (en partant de l'index 1)
- **Pomme** — compare la tête avec la case de la pomme

### Direction

La direction courante est stockée dans deux entiers `dx` / `dy` dans `main`. Les demi-tours sont interdits : on ne peut pas aller à gauche si on va à droite, etc.

---

## Constantes configurables

Définies dans `include/config.h` :

| Constante | Valeur par défaut | Description |
|---|---|---|
| `TAILLE_CASE` | `20` | Taille d'une case en pixels |
| `LONGUEUR_FENETRE` | `900` | Largeur de la fenêtre en pixels |
| `LARGEUR_FENETRE` | `600` | Hauteur de la fenêtre en pixels |
| `SIZE_MIN_FENETRE` | `0` | Borne minimale de la grille |

La vitesse du serpent (`0.15f` secondes par déplacement) est définie directement dans `main.c`.

---

## Licence

Distribué sous licence **MIT**.
