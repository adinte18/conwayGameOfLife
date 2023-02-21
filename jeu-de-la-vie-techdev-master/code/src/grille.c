#include "../include/grille.h"
#include <stdlib.h>

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", &vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	
	fclose (pfile);
	return;
}

//l = ligne ; c = colonne

void alloue_grille (int l, int c, grille* g)
{	g->nbl = l ;
 	g->nbc = c ;
	g->generation = 0;
 	g->cellules = (int** )malloc(l * sizeof(int*)) ;
 	for (int i=0 ; i<l ; i++ )
  		g->cellules[i] = calloc(c , sizeof(int)) ;
}

void libere_grille (grille* g)
{
 	for (int i=0; i<g->nbl; i++)
	{
		free(g->cellules[i]);
 	}
	free(g->cellules);
}

void make_non_viable(grille g)
{
	int i,j;
	printf("Give the line: ");
	while (scanf("%d", &i) != 1)
	{
		printf("You have given something else than an integer! ");
		printf("Retry >> Give the line: ");
		getchar();
	}
	printf("Give the row: ");
	while (scanf("%d", &j) != 1)
	{
		printf("You have given something else than an integer! \n");
		printf("Retry >> Give the row: ");
		getchar();
	}
	if (i < g.nbl && j < g.nbc){
		set_non_viable(i,j,g);
	}
}

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
