#include "entites.h"

// Initialisation des asteroides
void initAsteroides (Asteroide asteroides[], int couloirs[], int nb_couloirs)
{
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        asteroides[i].rect.x = couloirs[rand() % nb_couloirs];
        asteroides[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        asteroides[i].rect.w = TAILLE_ASTEROIDE;
        asteroides[i].rect.h = TAILLE_ASTEROIDE;
        asteroides[i].vitesse = 2 + rand() % 5;
    }
}
    
// Initialisation des etoiles
void initEtoiles (Etoile etoiles[])
{
    for (int i = 0; i < MAX_ETOILES; i++)
    {
        etoiles[i].rect.x = rand() % (LARGEUR_FENETRE - TAILLE_ETOILE);
        etoiles[i].rect.y = -(rand() % HAUTEUR_FENETRE);
        etoiles[i].rect.w = TAILLE_ETOILE;
        etoiles[i].rect.h = TAILLE_ETOILE;
        etoiles[i].vitesse = 2 + rand() % 5;
    }
}

// MAJ positions asteroides si ils sortent de l'ecran
void majAsteroides (Asteroide asteroides[], int couloirs[], int nb_couloirs)
{
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
}

// MAJ positions etoiles si elles sortent de l'ecran
void majEtoiles (Etoile etoiles[])
{
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
}
