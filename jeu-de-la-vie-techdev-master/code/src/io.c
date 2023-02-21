#include "../include/io.h"
#include "../include/grille.h"
#include "../include/jeu.h"

int cyclic = 0;
int aging = 0;
int osc;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); 
		else 
		{ 
			if (aging == 1)
			{
				printf("| %d ", ligne[i]);
			}
			else if (ligne[i] == -1)
			{
				printf("| X ");
			}
			else
			{
				printf("| 0 "); 
			}
			
		}
	printf("|\n");
	return;
}

void show_menu()
{
	printf("================================MENU========================================== \n");
	printf("Press 'N' -- to initialize a new grid from a file (/grilles/grille#.txt) \n");
	printf("Press 'C' -- to change the mode \n");
	printf("Press 'V' -- to activate aging \n");
	printf("Press 'Q' -- to quit \n"); 
	printf("Press 'S' -- to set non viable a cell \n");
	printf("Press 'O' -- to test if a grid is oscillating or not \n");
	printf("============================================================================== \n");
}

void show_aging()
{
	printf("Aging : %d \n", aging == 1 ? 1 : 0);
}

void show_mode()
{
	printf(" Cyclic mode : %d ", cyclic);
}

void affiche_grille (grille g){
	system("clear");
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("------------------------------------------------- \n");
	printf("Generations : %d ", g.generation);
	printf(" | ");
	show_mode();
	printf(" | ");
	show_aging();
	printf("------------------------------------------------- \n");
	printf("New grid!\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n");
	show_menu();
	return;
}
 
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc)
{
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}

			case 'n' :
			{
				printf("Enter the path of the file: ");
				char path[30];
				scanf("%s", path);
				while (fileExists(path) == false){
					printf("The path : %s that you entered does not exist \n", path);
					printf("Enter a new one : ");
					scanf("%s", path);
				}
				efface_grille(*g);
				libere_grille(gc); 
				libere_grille(g);
				init_grille_from_file(path, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				break;
			}
			case 'v':
			{
				aging = !aging;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'c' : 
			{
				cyclic = !cyclic;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}

			case 's' :
			{
				make_non_viable(*g);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'o' :
			{
				osc = oscilation(g);
				if (osc < 500)
				{
					printf("The grid does not seem to be oscillating \n");
				}
				else printf("Oscillates over a period of : %d \n", osc);
				c = getchar();

				break;
			}

			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
