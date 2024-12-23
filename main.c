#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Fenetre
#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 800

// Boutons
#define LARGEUR_BOUTON 300
#define HAUTEUR_BOUTON 100

// Fusee
#define LARGEUR_FUSEE 100
#define HAUTEUR_FUSEE 100

// Asteroides
#define TAILLE_ASTEROIDE 50
#define MAX_ASTEROIDES 15

// Etoiles
#define TAILLE_ETOILE 3
#define MAX_ETOILES 100

typedef struct Asteroide_
{
    SDL_Rect rect;
    int vitesse;
}Asteroide;

typedef struct Etoile_
{
    SDL_Rect rect;
    int vitesse;
}Etoile;

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

int main(int argc, char *argv[])
{
    // Initialisation
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    // Creation fenetre + rendu
    if (SDL_CreateWindowAndRenderer(LARGEUR_FENETRE, HAUTEUR_FENETRE, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Creation fenetre et rendu");

    // Execution du programme

    /*-----------Arriere plan------------*/

    SDL_Surface *image_arriere_plan = NULL;
    SDL_Texture *texture_arriere_plan = NULL;
    
    //Creation texture arriere plan
    MySDL_CreateTexture(window, renderer, &image_arriere_plan, &texture_arriere_plan, "/home/madjid/Documents/C/Projet/Images/subtle_space_background.bmp");
        
    //Encadrement pour la texture arriere plan
    SDL_Rect rectangle_texture;
    
    //Chargement en memoire de la texture arriere plan
    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, &rectangle_texture.w, &rectangle_texture.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement en memoire texture arriere plan");
        
    /*Rajouter ces 2 ligne pour que la texture occupe toute la fenetre
    rectangle_texture.w = LARGEUR_FENETRE;
    rectangle_texture.h = HAUTEUR_FENETRE;
    */
	
    //Centrer la texture par rapport a la fenetre
    rectangle_texture.x = (LARGEUR_FENETRE - rectangle_texture.w) / 2;
    rectangle_texture.y = (HAUTEUR_FENETRE - rectangle_texture.h) / 2;

    /*-----------Boutons------------*/
  
    //Initialisation
    SDL_Surface *image_bouton_start = NULL;
    SDL_Surface *image_bouton_exit = NULL;
    SDL_Texture *texture_bouton_start = NULL;
    SDL_Texture *texture_bouton_exit = NULL;

    //Encadrement pour bouton start
    SDL_Rect rectangle_bouton_start = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, HAUTEUR_FENETRE / 3 - HAUTEUR_BOUTON / 2, 0, 0};
    
    //Creation texture bouton start
    MySDL_CreateTexture(window, renderer, &image_bouton_start, &texture_bouton_start, "/home/madjid/Documents/C/Projet/Images/start.bmp");

    //Chargement en memoire de la texture bouton start
    if (SDL_QueryTexture(texture_bouton_start, NULL, NULL, &rectangle_bouton_start.w, &rectangle_bouton_start.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture bouton start");

    //Encadrement pour bouton exit
    SDL_Rect rectangle_bouton_exit = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, 2 * HAUTEUR_FENETRE / 3 - HAUTEUR_BOUTON / 2, 0, 0};
    
    //Creation texture bouton exit
    MySDL_CreateTexture(window, renderer, &image_bouton_exit, &texture_bouton_exit, "/home/madjid/Documents/C/Projet/Images/exit.bmp");

    //Chargement en memoire de la texture bouton exit
    if (SDL_QueryTexture(texture_bouton_exit, NULL, NULL, &rectangle_bouton_exit.w, &rectangle_bouton_exit.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture bouton exit");

    /*----------------Fusee-----------------*/

    // Initialisation
    SDL_Surface *image_fusee = NULL;
    SDL_Texture *texture_fusee = NULL;
    
    //Encadrement pour la fusee
    SDL_Rect rectangle_fusee = {LARGEUR_FENETRE / 2 - LARGEUR_FUSEE / 2, HAUTEUR_FENETRE - HAUTEUR_FUSEE, 0, 0};
    
    //Creation texture fusee
    MySDL_CreateTexture(window, renderer, &image_fusee, &texture_fusee, "/home/madjid/Documents/C/Projet/Images/fusee.bmp");

    //Chargement en memoire de la texture fusee
    if (SDL_QueryTexture(texture_fusee, NULL, NULL, &rectangle_fusee.w, &rectangle_fusee.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture fusee");
        
    /*----------------Asteroides-----------------*/
    
    // Initialisation
    SDL_Surface *image_asteroide = NULL;
    SDL_Texture *texture_asteroide = NULL;
    
    // Tableau d'asteroides
    Asteroide asteroides[MAX_ASTEROIDES];
    
    // Encadrement pour les asteroides
    SDL_Rect rectangle_asteroide = {LARGEUR_FENETRE / 2 - TAILLE_ASTEROIDE / 2, TAILLE_ASTEROIDE, 0, 0};
    
    // Definir des couloirs
    int nb_couloirs = 5;
    int couloirs[] = {87, 287, 487, 687, 887};
    
    // Initialisation des asteroides
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        asteroides[i].rect.x = couloirs[rand() % nb_couloirs];
        asteroides[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        asteroides[i].rect.w = TAILLE_ASTEROIDE;
        asteroides[i].rect.h = TAILLE_ASTEROIDE;
        asteroides[i].vitesse = 2 + rand() % 5;
    }

    // Creation texture asteroide
    MySDL_CreateTexture(window, renderer, &image_asteroide, &texture_asteroide, "/home/madjid/Documents/C/Projet/Images/asteroide.bmp");
    
    // Chargement en memoire de la texture asteroide
    if (SDL_QueryTexture(texture_asteroide, NULL, NULL, &rectangle_asteroide.w, &rectangle_asteroide.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture asteroide");
        
    /*------------------Etoiles-----------------*/
    
        // Initialisation
    SDL_Surface *image_etoile = NULL;
    SDL_Texture *texture_etoile = NULL;
    
    // Tableau d'etoiles
    Etoile etoiles[MAX_ETOILES];
    
    // Encadrement pour les etoiles
    SDL_Rect rectangle_etoile = {LARGEUR_FENETRE / 2 - TAILLE_ETOILE / 2, TAILLE_ETOILE, 0, 0};
    
    // Initialisation des etoiles
    for (int i = 0; i < MAX_ETOILES; i++)
    {
        etoiles[i].rect.x = rand() % (LARGEUR_FENETRE - TAILLE_ETOILE);
        etoiles[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        etoiles[i].rect.w = TAILLE_ETOILE;
        etoiles[i].rect.h = TAILLE_ETOILE;
        etoiles[i].vitesse = 2 + rand() % 5;
    }

    // Creation texture etoiles
    MySDL_CreateTexture(window, renderer, &image_etoile, &texture_etoile, "/home/madjid/Documents/C/Projet/Images/etoiles.bmp");
    
    // Chargement en memoire de la texture etoile
    if (SDL_QueryTexture(texture_etoile, NULL, NULL, &rectangle_etoile.w, &rectangle_etoile.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture etoile");
        
    /*------------------------------------------*/
    
    // Afficher ou pas les boutons (affcihes par defaut)
    SDL_bool afficher_boutons = SDL_TRUE;

    // MAJ du rendu 
    SDL_RenderPresent(renderer);

    /*----------------------------------------------------------------------------------*/
    // Gestion des evenements clavier souris

    SDL_bool program_launched = SDL_TRUE;
    while (program_launched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    if(rectangle_fusee.x < 862)
                      rectangle_fusee.x += 200;
                    continue;
                case SDLK_LEFT:
                    if(rectangle_fusee.x > 62)
                      rectangle_fusee.x -= 200;
                    continue;
                default:
                    continue;
                }

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= rectangle_bouton_start.x && x <= rectangle_bouton_start.x + rectangle_bouton_start.w &&
                        y >= rectangle_bouton_start.y && y <= rectangle_bouton_start.y + rectangle_bouton_start.h)
                    {
                        afficher_boutons = SDL_FALSE;
                    }

                    if (x >= rectangle_bouton_exit.x && x <= rectangle_bouton_exit.x + rectangle_bouton_exit.w &&
                        y >= rectangle_bouton_exit.y && y <= rectangle_bouton_exit.y + rectangle_bouton_exit.h)
                    {
                        program_launched = SDL_FALSE;
                    }
                }
                break;

            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;

            default:
                break;
            }
        }
        
        // Evenements liés aux asteroides (!affiche_bouton car sinon les asteroides se generent avant start et je peux perdre avant de commencer)
        if (!afficher_boutons)
        {
            // MAJ positions asteroides si ils sortent de l'ecran
            for (int i = 0; i < MAX_ASTEROIDES; i++) 
            {
                asteroides[i].rect.y += asteroides[i].vitesse;

                // Reinitialiser la position si l'asteroide sort de l'ecran
                if (asteroides[i].rect.y > HAUTEUR_FENETRE) 
                {
                    asteroides[i].rect.x = couloirs[rand() % nb_couloirs];
                    asteroides[i].rect.y = -(rand() % HAUTEUR_FENETRE);
                    asteroides[i].vitesse = 2 + rand() % 5;
                }
            }
            
            // Detection collisions 
            for (int i = 0; i < MAX_ASTEROIDES; i++) 
            {
                if (SDL_HasIntersection(&rectangle_fusee, &asteroides[i].rect)) 
                {
                    //Explosion();
                    //GameOver();
                }
            }
        }
        
        // MAJ positions etoiles si ils sortent de l'ecran
        for (int i = 0; i < MAX_ETOILES; i++) 
        {
            etoiles[i].rect.y += etoiles[i].vitesse;

            // Reinitialiser la position si l'etoile sort de l'écran
            if (etoiles[i].rect.y > HAUTEUR_FENETRE) 
            {
                etoiles[i].rect.x = rand() % (LARGEUR_FENETRE - TAILLE_ETOILE);
                etoiles[i].rect.y = -(rand() % HAUTEUR_FENETRE);
                etoiles[i].vitesse = 2 + rand() % 5;
            }
        }
        
        /*----------------Affichage----------------*/
        
        // Effacer les textures qui sont sur le rendu et afficher seulement l'arriere plan et les etoiles
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture_arriere_plan, NULL, &rectangle_texture);

        for (int i = 0; i < MAX_ETOILES; i++) {
            SDL_RenderCopy(renderer, texture_etoile, NULL, &etoiles[i].rect);
        }
        
        // Afficher ou les boutons ou la fusee&asteroides en plus de l'arriere plan
        if (afficher_boutons)
        {
            SDL_RenderCopy(renderer, texture_bouton_start, NULL, &rectangle_bouton_start);
            SDL_RenderCopy(renderer, texture_bouton_exit, NULL, &rectangle_bouton_exit);
        }
        else
        {
            SDL_RenderCopy(renderer, texture_fusee, NULL, &rectangle_fusee);
            for (int i = 0; i < MAX_ASTEROIDES; i++) {
                SDL_RenderCopy(renderer, texture_asteroide, NULL, &asteroides[i].rect);
            }
            
        }
  
        // MAJ rendu
        SDL_RenderPresent(renderer);
    }

    /*----------------------------------------------------------------------------------*/

    SDL_DestroyTexture(texture_arriere_plan);
    SDL_DestroyTexture(texture_bouton_start);
    SDL_DestroyTexture(texture_bouton_exit);
    SDL_DestroyTexture(texture_fusee);
    SDL_DestroyTexture(texture_asteroide);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
