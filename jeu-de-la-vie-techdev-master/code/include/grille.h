#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/**
 * @file grille.h
 * @brief Fichier "header" contenant les fonctions liees aux grilles
 */


/**
 * @brief Structure grille
 * @param nbl entier representant le nombre de lignes
 * @param nbc entier representant le nombre de colonnes
 * @param cellules tableau2D de cellules
 * @param generation la generation d'une grille
*/

typedef struct {int nbl; int nbc; int** cellules; int generation;} grille;

//alloue une grille de taille l*c, et initialise toutes les cellules à mortes

/** 
 * @brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes(0); 
 * @param l un entier designant les lignes
 * @param c un entier designant les colonnes
 * @param g un pointeur sur la grille
 */

void alloue_grille (int l, int c, grille* g);

// libère une grille

/**
 * @brief Libère la memoire alloue a la grille
 * @param g pointeur vers la grille à liberer
 */

void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier

/**
 * @brief Initialise une grille g a l'aide d'une fichier
 * @param filename pointeur vers le fichier contenant les donnees pour initialiser une nouvelle grille
 * @param g pointeur vers la grille initialise a partir le fichier
 */

void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g

/** 
 * @brief Rend la cellule(i,j) de la grille g vivante; 
 * @param l un entier designant les lignes
 * @param c un entier designant les colonnes
 * @param g variable pour la grille
 */

static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

// rend morte la cellule (i,j) de la grille g

/** 
 * @brief Rend la cellule(i,j) de la grille g morte; 
 * @param l un entier designant les lignes
 * @param c un entier designant les colonnes
 * @param g variable pour la grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante

/** 
 * @brief Teste si la cellule (i,j) de la grille g est vivante; 
 * @param l un entier designant les lignes
 * @param c un entier designant les colonnes
 * @param g variable pour la grille
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1 && g.cellules[i][j] != 9;}

//teste si la cellule (i,j) de la grille g est vivante dans le mode non-cyclique

/**
 * @brief La fonction teste si la cellule (i,j) de la grille g est vivante dans le mode non-cyclique.
 * @param l un entier designant les lignes
 * @param c un entier designant les colonnes
 * @param g grille contenant la cellule
 */
static inline int est_vivante_noncyclique(int i, int j, grille g)
{
    if (i>=g.nbl || j>=g.nbc || i<0 || j<0)
        return 0;
    return g.cellules[i][j] >= 1 && g.cellules[i][j] !=9;
}

//incremente les valeurs d'une cellule(i,j)

/**
 * @brief Fonction pour incrementer les valeurs d'une cellule(i,j)
 * @param i variable pour les lignes
 * @param j variable pour les colonnes
 * @param g variable pour la grille
*/

static inline void incremente(int i , int j , grille g){g.cellules[i][j]++;};


/**
 * @brief Fonction pour faire une cellule(i,j) non viable
 * @param g variable pour la grille
*/
void make_non_viable(grille g);


/** 
 * @brief Fonction qui permets de rendre la cellule (i,j) non viable dans la grille g
 * @param i variable pour les lignes
 * @param j variable pour les colonnes
 * @param  g Pointeur de grille
*/

static inline int set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;};

// recopie gs dans gd (sans allocation)

/**
 * @brief Fonction qui recopie gs dans gd (sans allocation)
 * @param gs la grille origine
 * @param gd la grille copie
*/

void copie_grille (grille gs, grille gd);

#endif
