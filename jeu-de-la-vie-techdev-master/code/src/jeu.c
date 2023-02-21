#include "../include/jeu.h"
#include "../include/grille.h"

int aging;
int cyclic;

int *compte_voisins_vivants (int i, int j, grille g)
{
	int *v = 0, l=g.nbl, c = g.nbc;
	int a = 0;
	v = &a;
	if (cyclic == 0)
	{
		a+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
		a+= est_vivante(modulo(i-1,l),modulo(j,c),g);
		a+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
		a+= est_vivante(modulo(i,l),modulo(j-1,c),g);
		a+= est_vivante(modulo(i,l),modulo(j+1,c),g);
		a+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
		a+= est_vivante(modulo(i+1,l),modulo(j,c),g);
		a+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	}
	else 
	{
		a+= est_vivante_noncyclique(i-1, j-1, g);
		a+= est_vivante_noncyclique(i-1, j, g);
		a+= est_vivante_noncyclique(i-1, j+1, g);
		a+= est_vivante_noncyclique(i, j-1, g);
		a+= est_vivante_noncyclique(i, j+1, g);
		a+= est_vivante_noncyclique(i+1, j-1, g);
		a+= est_vivante_noncyclique(i+1, j, g);
		a+= est_vivante_noncyclique(i+1, j+1, g);
	}
	
	return v; 
}


void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	g->generation++;
	int i,j,l=g->nbl, c = g->nbc, *v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);

			if (est_vivante(i, j, *g))
			{
				if (g->cellules[i][j] == 8)
					set_morte(i, j, *g);

				else
				{
					if (aging == 1)
						{incremente(i,j,*g);}
					else
						{g->cellules[i][j] = 1;}
				}
				
				if (*v != 2 && *v != 3)
					{set_morte(i,j,*g);}
			}
			else
			{
				if (*v == 3)
					{set_vivante(i, j, *g);}
			}	
		}
	}

	for (i = 0; i<l; i++)
	{
		for (j = 0; j<c; j++)
		{
			if (g->cellules[i][j] == 9)
				{g->cellules[i][j] =1;}
			if (g->cellules[i][j] == 11)
				{g->cellules[i][j] =0;}
		}
	}

	return;
}

int oscilation(grille *g)
{
	int l = g->nbl;
	int c = g->nbc;

	grille gc1, gc2;

	alloue_grille(l, c, &gc1);
	alloue_grille(l, c, &gc2);

	copie_grille(*g, gc1);

	int temps = 0;

	evolue(&gc1, &gc2);
	while( testEgal(&gc1, &gc2) != 1 && temps < 500 )
	{
			evolue(&gc1, &gc2);
			temps++;
	}

	libere_grille(&gc1);
	libere_grille(&gc2);

	return temps;
}

int testEgal(grille *g, grille *gc)
{
	int l = g->nbl;
	int c = g->nbc;

	for (int i = 0 ; i < l; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if(g->cellules[i][j] != gc->cellules[i][j])
				return 0; // false
		}
	}
	return 1; // true
}
