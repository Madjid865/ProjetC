**Jeu 2D en C avec SDL2**

Ce projet est un jeu 2D développé en langage C à l'aide de la bibliothèque SDL2, réalisé dans le cadre d'un projet scolaire de programmation. Le jeu consiste à contrôler une fusée qui doit esquiver des astéroïdes dans un environnement spatial.

**Fonctionnalités**
- Affichage dynamique d'un arrière-plan étoilé.
- Mouvement de la fusée contrôlée par le joueur.
- Génération et mise à jour des astéroïdes et étoiles.
- Gestion des collisions entre la fusée et les astéroïdes.
- Système de score avec affichage d'un commentaire de performance en fin de partie.
- Interface utilisateur avec boutons Start et Exit.

**Prérequis** 
Pour compiler et exécuter le jeu, vous aurez besoin de
- SDL2 et SDL2_ttf installés sur votre machine.
- Un compilateur C (comme gcc).
- Un système Linux (ou tout autre système compatible avec la SDL2).

**Instructions d'installation**
- Clonez le dépôt :
  _git clone https://github.com/Madjid865/ProjetC.git
  cd ProjetC_
- Installez les bibliothèques SDL2 (si ce n'est pas encore fait) :
  _sudo apt-get install libsdl2-dev libsdl2-ttf-dev_
- Vérifiez les chemins vers les images : Modifiez les chemins des éléments suivants dans votre code source :
  Arrière-plan
  Boutons Start et Exit
  Fusée
  Astéroïde
Les chemins doivent pointer vers les fichiers correspondants dans le dossier Images.

- Compilez le projet à l'aide du Makefile :
  _make_
- Exécutez le jeu :
  ._/game_
  
**Structure du projet**
main.c : Point d'entrée du programme.
entites.c/.h : Gestion des structures et mises à jour des entités (astéroïdes, étoiles).
graphique.c/.h : Chargement et affichage des textures et graphiques.
jeu.c/.h : Gestion de la logique de jeu (collisions, scores, réinitialisation).
constantes.h : Définit les dimensions et constantes du jeu.
Images/ : Contient les images nécessaires au jeu.
