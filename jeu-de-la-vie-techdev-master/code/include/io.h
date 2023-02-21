#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include <unistd.h>
#include <stdbool.h>

/**
 * @file io.h
 * @brief Fichier "header" contenant les fonctions liees a l'affichage de jeu
*/

// affichage d'un trait horizontal

/**
 * @brief Fonction utilise pour afficher un trait horizontal
 * @param c entier representant la longueur du trait
*/
void affiche_trait (int c);

// affichage d'une ligne de la grille

/**
 * @brief Fonction utilise pour afficher un trait horizontal
 * @param c entier representant la longueur de la ligne
 * @param ligne pointeur vers la ligne  
*/
void affiche_ligne (int c, int* ligne);

// affichage d'une grille

/**
 * @brief Fonction utilise pour afficher la grille
 * @param g la grille 
*/
void affiche_grille (grille g);

// effacement d'une grille

/**
 * @brief Fonction utilise pour effacer la grille 
 * @param g la grille a effacer
*/
void efface_grille (grille g);

// debute le jeu

/**
 * @brief Fonction utilise pour le debut de jeu
 * @param g pointeur vers la grille 
 * @param gc pointeur vers la grille copie
*/
void debut_jeu(grille *g, grille *gc);

//test path

/**
 * @brief Fonction utilise pour verifier si le fichier existe
 * @param path le chemin d'un fichier
*/
static bool fileExists(char *path)
{
    if (access(path, F_OK) != -1)
    {
        return true;
    }
    else
        return false;
}

#endif
