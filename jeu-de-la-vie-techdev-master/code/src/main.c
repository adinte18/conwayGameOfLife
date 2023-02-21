#include <stdio.h>

#include "../include/grille.h"
#include "../include/jeu.h"

#ifdef GRAPHIC
#include "../include/graphic.h"
#else
#include "../include/io.h"
#endif

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	int choice;
	printf("Do you want to set a cell non-viable? [1 = yes/ 0 = no] : ");
	scanf("%d", &choice);
	if (choice == 1)
	{
		make_non_viable(g);
		debut_jeu(&g, &gc);
	}
	else debut_jeu(&g, &gc);
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
