#ifndef __ENTITES_H__
#define __ENTITES_H__

#include <SDL.h>
#include <stdlib.h>
#include "constantes.h"

typedef struct Asteroide
{
    SDL_Rect rect;
    int vitesse;
}Asteroide;

typedef struct Etoile
{
    SDL_Rect rect;
    int vitesse;
}Etoile;

void initAsteroides (Asteroide asteroides[], int couloirs[], int nb_couloirs);
void initEtoiles (Etoile etoiles[]);
void majAsteroides (Asteroide asteroides[], int couloirs[], int nb_couloirs);
void majEtoiles (Etoile etoiles[]);

#endif
