#include "jeu.h"

void LancerJeu(SDL_Window *window, SDL_Renderer *renderer)
{
    // Initialisation des variables du jeu, des textures, etc.
    int score = 0;
    SDL_Surface *image_arriere_plan = NULL; // Arriere plan
    SDL_Texture *texture_arriere_plan = NULL;
    SDL_Surface *image_bouton_start = NULL; // Boutons
    SDL_Surface *image_bouton_exit = NULL;
    SDL_Texture *texture_bouton_start = NULL;
    SDL_Texture *texture_bouton_exit = NULL;
    SDL_Surface *image_fusee = NULL; // Fusee
    SDL_Texture *texture_fusee = NULL;
    SDL_Surface *image_asteroide = NULL; // Asteroides
    SDL_Texture *texture_asteroide = NULL;
    SDL_Surface *image_etoile = NULL; // Etoiles
    SDL_Texture *texture_etoile = NULL;
    if (TTF_Init() == -1) // SDL_ttf
        SDL_ExitWithError("Initialisation SDL_ttf");
        
    /*-----------Arriere plan------------*/
    
    // Creation texture arriere plan
    MySDL_CreateTexture(window, renderer, &image_arriere_plan, &texture_arriere_plan, "/home/madjid/Documents/C/Projet/Images/subtle_space_background.bmp");
        
    // Encadrement pour la texture arriere plan
    SDL_Rect rectangle_texture;
    
    // Chargement en memoire de la texture arriere plan
    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, &rectangle_texture.w, &rectangle_texture.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement en memoire texture arriere plan");
        
    /*Rajouter ces 2 ligne pour que la texture occupe toute la fenetre
    rectangle_texture.w = LARGEUR_FENETRE;
    rectangle_texture.h = HAUTEUR_FENETRE;
    */
	
    // Centrer la texture par rapport a la fenetre
    rectangle_texture.x = (LARGEUR_FENETRE - rectangle_texture.w) / 2;
    rectangle_texture.y = (HAUTEUR_FENETRE - rectangle_texture.h) / 2;
    
    /*-----------Boutons------------*/
    
    // Encadrement pour bouton start
    SDL_Rect rectangle_bouton_start = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, HAUTEUR_FENETRE / 3 - HAUTEUR_BOUTON / 2, 0, 0};
    
    // Creation texture bouton start
    MySDL_CreateTexture(window, renderer, &image_bouton_start, &texture_bouton_start, "/home/madjid/Documents/C/Projet/Images/start.bmp");

    // Chargement en memoire de la texture bouton start
    if (SDL_QueryTexture(texture_bouton_start, NULL, NULL, &rectangle_bouton_start.w, &rectangle_bouton_start.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture bouton start");

    // Encadrement pour bouton exit
    SDL_Rect rectangle_bouton_exit = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, 2 * HAUTEUR_FENETRE / 3 - HAUTEUR_BOUTON / 2, 0, 0};
    
    // Creation texture bouton exit
    MySDL_CreateTexture(window, renderer, &image_bouton_exit, &texture_bouton_exit, "/home/madjid/Documents/C/Projet/Images/exit.bmp");

    // Chargement en memoire de la texture bouton exit
    if (SDL_QueryTexture(texture_bouton_exit, NULL, NULL, &rectangle_bouton_exit.w, &rectangle_bouton_exit.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture bouton exit");
        
    /*----------------Fusee-----------------*/
    
    // Encadrement pour la fusee
    SDL_Rect rectangle_fusee = {LARGEUR_FENETRE / 2 - LARGEUR_FUSEE / 2, HAUTEUR_FENETRE - HAUTEUR_FUSEE, 0, 0};
    
    // Creation texture fusee
    MySDL_CreateTexture(window, renderer, &image_fusee, &texture_fusee, "/home/madjid/Documents/C/Projet/Images/fusee.bmp");

    // Chargement en memoire de la texture fusee
    if (SDL_QueryTexture(texture_fusee, NULL, NULL, &rectangle_fusee.w, &rectangle_fusee.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture fusee");
    
    /*----------------Asteroides-----------------*/
    
    // Tableau d'asteroides
    Asteroide asteroides[MAX_ASTEROIDES];
    
    // Encadrement pour les asteroides
    SDL_Rect rectangle_asteroide = {LARGEUR_FENETRE / 2 - TAILLE_ASTEROIDE / 2, TAILLE_ASTEROIDE, 0, 0};
    
    // Definir des couloirs
    int nb_couloirs = 5;
    int couloirs[] = {87, 287, 487, 687, 887};
    
    // Initialisation des asteroides
    initAsteroides (asteroides, couloirs, nb_couloirs);
    
    // Creation texture asteroide
    MySDL_CreateTexture(window, renderer, &image_asteroide, &texture_asteroide, "/home/madjid/Documents/C/Projet/Images/asteroide.bmp");
    
    // Chargement en memoire de la texture asteroide
    if (SDL_QueryTexture(texture_asteroide, NULL, NULL, &rectangle_asteroide.w, &rectangle_asteroide.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture asteroide");
        
    // Tableau d'etoiles
    Etoile etoiles[MAX_ETOILES];
    
    // Encadrement pour les etoiles
    SDL_Rect rectangle_etoile = {LARGEUR_FENETRE / 2 - TAILLE_ETOILE / 2, TAILLE_ETOILE, 0, 0};
    
    // Initialisation des etoiles
    initEtoiles (etoiles);
    
    // Creation texture etoiles
    MySDL_CreateTexture(window, renderer, &image_etoile, &texture_etoile, "/home/madjid/Documents/C/Projet/Images/etoiles.bmp");
    
    // Chargement en memoire de la texture etoile
    if (SDL_QueryTexture(texture_etoile, NULL, NULL, &rectangle_etoile.w, &rectangle_etoile.h) != 0)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement texture etoile");
        
    /*------------------Texte-----------------*/
    
    // Charger une police
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 40);
    if (font == NULL)
        SDL_ExitWithError("Chargement de la police");

    // Couleur pour le texte
    SDL_Color white = {255, 255, 255, 255};
    
    /*------------------------------------------*/
    
    // Afficher ou pas les boutons (affcihes par defaut)
    SDL_bool afficher_boutons = SDL_TRUE;

    // MAJ du rendu 
    SDL_RenderPresent(renderer);
    
    // Boucle de jeu principale
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
            // Tant que le jeu est en cours, incrementer le score
            score++;
            
            // MAJ positions asteroides si ils sortent de l'ecran
            majAsteroides (asteroides, couloirs, nb_couloirs);
            
            // Afficher le score pendant le jeu
            char score_text[50];
            snprintf(score_text, sizeof(score_text), "Score: %d", score);

            SDL_Rect score_position = {10, 10, 150, 30}; 
            MySDL_RenderText(renderer, font, score_text, white, &score_position);

            // MAJ rendu
            SDL_RenderPresent(renderer);
            
            // Detection collisions 
            for (int i = 0; i < MAX_ASTEROIDES; i++) 
            {
                if (SDL_HasIntersection(&rectangle_fusee, &asteroides[i].rect)) 
                {                    
                    // Afficher le score final avec la texture arriere plan
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture_arriere_plan, NULL, &rectangle_texture);
                    
                    char final_text[100];
                    if (score < 1000) {
                        snprintf(final_text, sizeof(final_text), "Score: %d - Nuuuul !", score);
                    } else if (score < 2000) {
                        snprintf(final_text, sizeof(final_text), "Score: %d - Pas maaal !", score);
                    } else if (score < 3000) {
                        snprintf(final_text, sizeof(final_text), "Score: %d - Y'a du niveau !", score);
                    } else {
                        snprintf(final_text, sizeof(final_text), "Score: %d - Trop fort !", score);
                    }

                    SDL_Rect final_text_position = {LARGEUR_FENETRE / 2 - 150, HAUTEUR_FENETRE / 2 - 30, 300, 60};
                    MySDL_RenderText(renderer, font, final_text, white, &final_text_position);

                    SDL_RenderPresent(renderer);
                    SDL_Delay(5000); // Attendre pour que le joueur ai le temps de voir son score
                    
                    // Reinitialiser le tout et proposer start ou exit 
                    RelancerJeu(nb_couloirs, couloirs, asteroides, etoiles, &score, &rectangle_fusee, &afficher_boutons);
                }
            }
        }
        
        // MAJ positions etoiles si elles sortent de l'ecran
        majEtoiles (etoiles);
        
        /*----------------Affichage----------------*/
        
        // Effacer les textures qui sont sur le rendu et afficher seulement l'arriere plan et les etoiles
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture_arriere_plan, NULL, &rectangle_texture);

        for (int i = 0; i < MAX_ETOILES; i++) {
            SDL_RenderCopy(renderer, texture_etoile, NULL, &etoiles[i].rect);
        }
        
        // Afficher ou les boutons ou la fusee & asteroides en plus de l'arriere plan
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
    TTF_CloseFont(font);
    TTF_Quit();
}

void RelancerJeu(int nb_couloirs, int couloirs[], Asteroide asteroides[], Etoile etoiles[], int *score, SDL_Rect *rectangle_fusee, SDL_bool *afficher_boutons)
{
    // Reinitialisation position des asteroides
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        asteroides[i].rect.x = couloirs[rand() % nb_couloirs];
        asteroides[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        asteroides[i].rect.w = TAILLE_ASTEROIDE;
        asteroides[i].rect.h = TAILLE_ASTEROIDE;
        asteroides[i].vitesse = 2 + rand() % 5;
    }
    
    // Reinitialisation position des etoiles
    for (int i = 0; i < MAX_ETOILES; i++)
    {
        etoiles[i].rect.x = rand() % (LARGEUR_FENETRE - TAILLE_ETOILE);
        etoiles[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        etoiles[i].rect.w = TAILLE_ETOILE;
        etoiles[i].rect.h = TAILLE_ETOILE;
        etoiles[i].vitesse = 2 + rand() % 5;
    }
    
    // Reinitialisation position de la fusee
    rectangle_fusee -> x = LARGEUR_FENETRE / 2 - LARGEUR_FUSEE / 2;
    rectangle_fusee -> y = HAUTEUR_FENETRE - HAUTEUR_FUSEE;
    
    // Reinitialisation score et afffichage start / exit
    *score = 0;
    *afficher_boutons = SDL_TRUE;
}
