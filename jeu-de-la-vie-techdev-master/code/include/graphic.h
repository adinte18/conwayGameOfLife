#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include "grille.h"
#include "jeu.h"
#include <unistd.h>
#include <stdbool.h>
/**
 * @file graphic.h
 * @brief Fichier "header" contenant les fonctions liees au mode graphique du jeu
*/


extern int aging; /*!< Variable extern int, utilisée a l'activation(en mode graphique) du viellissement d'une cellule*/
extern int cyclic; /*!< Variable extern int, utilisée pour representer(en mode graphique) le mode de calcul de cyclique à non-cyclique*/


/**
 * @brief Fonction qui crée la grille graphique
 * @param current_state pointeur vers l'état actuel du dispositif d'interpretation 
 * @param g pointer vers la grille
*/
void grid(cairo_t* current_state, grille *g);

/**
 * @brief Fonction qui permets de demarrer le jeu en mode graphique
 * @param g pointeur vers la grille 
 * @param gc pointeur vers la grille copie
*/
void debut_jeu(grille *g, grille *gc);

/**
 * @brief Fonction qui dessine la grille graphique
 * @param surface pointeur vers la surface graphique 
 * @param g pointeur vers la grille
*/
void paint(cairo_surface_t *surface, grille *g);

/**
 * @brief Fonction qui permets de charger les fichiers *.txt dans le jeu en mode graphique
 * @param surface pointeur vers la surface graphique 
 * @param dpy pointeur vers le display
 * @param g pointeur vers la grille
 * @param gc pointeur vers la grille copie
*/
int chargement(cairo_surface_t *surface, Display *dpy, grille *g, grille *gc);


/**
 * @brief Fonction qui permets de verifier si le fichier entree existe
 * @param path le chemin d'un fichier
*/
static bool fileExistsCairo(char *path)
{
    if (access(path, F_OK) != -1)
    {
        return true;
    }
    else
        return false;
}

/**
 * @brief Fonction qui permets de verifier si la grille oscille ou pas
 * @param surface pointeur vers la surface graphique
 * @param g pointeur vers la grille
*/
int osc_graph(cairo_surface_t *surface, grille *g);

#endif
