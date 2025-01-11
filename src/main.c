#include "graphique.h"
#include "jeu.h"
#include "entites.h"
#include "constantes.h"

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    if (SDL_CreateWindowAndRenderer(LARGEUR_FENETRE, HAUTEUR_FENETRE, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Creation fenetre et rendu");

    // Démarrer le jeu
    LancerJeu(window, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

