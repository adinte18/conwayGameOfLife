#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * @file jeu.h
 * @brief Fichier "header" contenant les fonctions liees au jeu
 */

extern int cyclic; /*!< Variable extern int, utilisée pour representer le mode de calcul de cyclique à non-cyclique*/
extern int aging; /*!< Variable extern int, utilisée a l'activation du viellissement d'une cellule*/
extern int osc; /*!< Variable extern int, utilisée a l'activation du test d'oscilation d'une cellule*/
// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques

/**
 * @brief Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * @param i dividende de la division
 * @param m diviseur de la division 
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.

/**
 * @brief La fonction compte le nombre de voisins vivants de la cellule(i,j)
 * @param i Un entier indiquant les lignes
 * @param j Un entier indiquant les colonnes
 * @param g La grille
 */
int *compte_voisins_vivants (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps

/**
 * @brief La fonction est utilisé pour evoluer la grille g d'un pas de temps
 * @param g pointeur vers la grille
 * @param gc pointeur vers la grille copie 
 */
void evolue (grille *g, grille *gc);


/**
 * @brief La fonction est utilisé pour verifier si une grille oscille
 * @param g pointeur vers la grille
 */
int oscilation(grille *g);

/**
 * @brief La fonction est utilisé pour comparer deux grilles et verifier si elles sont égaux
 * @param gc pointeur vers la grille
 * @param gc2 pointeur vers la grille copie 
 */
int testEgal(grille *gc1, grille *gc2);

#endif
