#ifndef __JEU_H__
#define __JEU_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include "graphique.h"
#include "entites.h"

void LancerJeu(SDL_Window *window, SDL_Renderer *renderer);
void RelancerJeu(int nb_couloirs, int couloirs[], Asteroide asteroides[], Etoile etoiles[], int *score, SDL_Rect *rectangle_fusee, SDL_bool *afficher_boutons);

#endif
