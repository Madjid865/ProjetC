// gcc main.c -o prog $(sdl2-config --cflags --libs)
// ./prog

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

//Fenetre
#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 800

//Boutons
#define LARGEUR_BOUTON 300 //Correspond à la la largeur de l'image du bouton 
#define HAUTEUR_BOUTON 100 //Correspond à la la hauteur de l'image du bouton 

//Gestion des erreurs avant creation fenetre et rendu
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Gestion des erreurs et destruction fenetre et rendu
void SDL_ExitWithErrorAndDeleteWR(SDL_Window *window, SDL_Renderer *renderer,const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

//Creation textures boutons start et exit
void SDL_CreateButton(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface **image_bouton, SDL_Texture **texture_bouton ,const char *chemin_image_bouton)
{
    //Chargement image bouton
    *image_bouton = SDL_LoadBMP(chemin_image_bouton);
    if(*image_bouton == NULL)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement image bouton");
        
    //Creation texture bouton
    *texture_bouton = SDL_CreateTextureFromSurface(renderer, *image_bouton);
    SDL_FreeSurface(*image_bouton);
    if(*texture_bouton == NULL)
        SDL_ExitWithErrorAndDeleteWR(window, renderer, "Creation texture bouton");
}


int main (int argc, char *argv[])
{
        //Initialisation
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        
        //Lancement SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	    SDL_ExitWithError("Initialisation SDL");
	
	//Creation fenetre + rendu
	if(SDL_CreateWindowAndRenderer(LARGEUR_FENETRE, HAUTEUR_FENETRE, 0, &window, &renderer) != 0)
	    SDL_ExitWithError("Creation fenetre et rendu");
	
	//Execution du programme
	/*----------------------------------------------------------------------------------*/
	SDL_Surface *image_arriere_plan = NULL;
        SDL_Texture *texture_arriere_plan = NULL;
        
        //Chargement image arriere plan
        image_arriere_plan = SDL_LoadBMP("/home/madjid/Documents/C/Projet/Images/subtle_space_background.bmp");
        if(image_arriere_plan == NULL)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement image arrière plan");
	
	//Creation texture arriere plan
	texture_arriere_plan = SDL_CreateTextureFromSurface(renderer, image_arriere_plan);
	SDL_FreeSurface(image_arriere_plan);
	if(texture_arriere_plan == NULL)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Creation texture arriere plan");
        
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
	
        //Affichage image arriere plan
        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, &rectangle_texture) != 0)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Affichage texture arriere plan");
         
        /*-----------Boutons------------*/  
        //Initialisation
        SDL_Surface *image_bouton_start = NULL;
        SDL_Surface *image_bouton_exit = NULL;
        SDL_Texture *texture_bouton_start = NULL;
        SDL_Texture *texture_bouton_exit = NULL;
        
        //Encadrement pour bouton start
	SDL_Rect rectangle_bouton_start = {LARGEUR_FENETRE/2 - LARGEUR_BOUTON/2, HAUTEUR_FENETRE/3 - HAUTEUR_BOUTON/2, LARGEUR_BOUTON, HAUTEUR_BOUTON};
        
        SDL_CreateButton(window, renderer, &image_bouton_start, &texture_bouton_start, "/home/madjid/Documents/C/Projet/Images/start.bmp");
	
	//Chargement en memoire de la texture bouton start
        if(SDL_QueryTexture(texture_bouton_start, NULL, NULL, &rectangle_bouton_start.w, &rectangle_bouton_start.h) != 0)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement en memoire texture bouton start");
            
        //Affichage image bouton start
        if(SDL_RenderCopy(renderer, texture_bouton_start, NULL, &rectangle_bouton_start) != 0)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Affichage texture bouton start");
          
        SDL_CreateButton(window, renderer, &image_bouton_exit, &texture_bouton_exit, "/home/madjid/Documents/C/Projet/Images/exit.bmp");
        
        //Encadrement pour bouton exit
	SDL_Rect rectangle_bouton_exit = {LARGEUR_FENETRE/2 - LARGEUR_BOUTON/2, 2*HAUTEUR_FENETRE/3 - HAUTEUR_BOUTON/2, LARGEUR_BOUTON, HAUTEUR_BOUTON};
            
        //Chargement en memoire de la texture bouton exit
        if(SDL_QueryTexture(texture_bouton_exit, NULL, NULL, &rectangle_bouton_exit.w, &rectangle_bouton_exit.h) != 0)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Chargement en memoire texture bouton exit");
            
        //Affichage image bouton exit
        if(SDL_RenderCopy(renderer, texture_bouton_exit, NULL, &rectangle_bouton_exit) != 0)
            SDL_ExitWithErrorAndDeleteWR(window, renderer, "Affichage texture bouton exit");
	
        //MAJ du rendu   
        SDL_RenderPresent(renderer);
	
	/*----------------------------------------------------------------------------------*/
	//Gestion des evenements

	SDL_bool program_launched = SDL_TRUE;
	 while(program_launched)
	 {
	    SDL_Event event;
	    while(SDL_PollEvent(&event))
	    {
	        switch(event.type)
	        {
	            //Evenements clavier
	            case SDL_KEYDOWN:
	                switch(event.key.keysym.sym)
	                {
	                    case SDLK_RIGHT:
	                        //Faire bouger la fusee a droite
	                        printf("Mouvement vers la droite\n");
	                        continue;
	                    
	                    default:
	                        continue;
	                }
	            
	            //Evenemnts souris  
	            //Mouvement souris
	            case SDL_MOUSEMOTION:
	                //Faire des choses (par exemple selectionner start ou exit)
	                //printf("%d / %d\n", event.motion.x, event.motion.y);
	                continue;
	                
	            //Touches souris
	            case SDL_MOUSEBUTTONDOWN:
	                // Recuperer position du clic si clic droit
	                int x = event.button.x;
	                int y = event.button.y;
	                /*
	                if(event.button.button == SDL_BUTTON_LEFT)
	                {
	                    x = event.button.x;
	                    y = event.button.y;
	                }
	                */
	                //Verifier si le clic est dans le rectangle start
	                if(x >= (LARGEUR_FENETRE/2 - LARGEUR_BOUTON/2) && x<= (LARGEUR_FENETRE/2 + LARGEUR_BOUTON/2) && y >= (HAUTEUR_FENETRE/3 - HAUTEUR_BOUTON/2) && y <= (HAUTEUR_FENETRE/3 + HAUTEUR_BOUTON/2))
	                {
	                    printf("Clic sur bouton start en %d / %d\n", x, y);
	                }
	                
	                //Verifier si le clic est dans le rectangle exit
	                if(x >= (LARGEUR_FENETRE/2 - LARGEUR_BOUTON/2) && x<= (LARGEUR_FENETRE/2 + LARGEUR_BOUTON/2) && y >= (2*HAUTEUR_FENETRE/3 - HAUTEUR_BOUTON/2) && y <= (2*HAUTEUR_FENETRE/3 + HAUTEUR_BOUTON/2))
	                {
	                    printf("Clic sur bouton exit en %d / %d\n", x, y);
	                    program_launched = SDL_FALSE;
	                }
	                continue;
	                
	            case SDL_QUIT:
	                program_launched = SDL_FALSE;
	                break;
	            
	            default:
	              break;
	        }
	    }
	 }
	/*----------------------------------------------------------------------------------*/
	
	//Nettoyage/Libeerer memoire
	SDL_DestroyTexture(texture_arriere_plan);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
