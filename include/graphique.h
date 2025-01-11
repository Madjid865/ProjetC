#ifndef __GRAPHIQUE_H__
#define __GRAPHIQUE_H__

#include <SDL.h>
#include <SDL_ttf.h>

void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorAndDeleteWR(SDL_Window *window, SDL_Renderer *renderer, const char *message);
void MySDL_CreateTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface **image, SDL_Texture **texture, const char *chemin_image);
void MySDL_RenderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect *position);

#endif
