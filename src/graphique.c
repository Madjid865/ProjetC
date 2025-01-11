#include "graphique.h"

// Gestion des erreurs avant creation fenetre et rendu
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// Gestion des erreurs et destruction fenetre et rendu
void SDL_ExitWithErrorAndDeleteWR(SDL_Window *window, SDL_Renderer *renderer, const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

// Creation textures arriere-plan & boutons start et exit
void MySDL_CreateTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface **image, SDL_Texture **texture, const char *chemin_image)
{
    // Chargement image
    *image = SDL_LoadBMP(chemin_image);
    if (*image == NULL)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement image");

    // Creation texture
    *texture = SDL_CreateTextureFromSurface(renderer, *image);
    SDL_FreeSurface(*image);
    if (*texture == NULL)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Creation texture");
}

// Affichage texte
void MySDL_RenderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect *position) 
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, color);
    if (text_surface == NULL)
        SDL_ExitWithError("Erreur : creation surface texte");

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    if (text_texture == NULL)
        SDL_ExitWithError("Erreur : creation texture texte");

    SDL_RenderCopy(renderer, text_texture, NULL, position);
    SDL_DestroyTexture(text_texture);
}
