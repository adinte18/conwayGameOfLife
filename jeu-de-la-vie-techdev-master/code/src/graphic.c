// fonction pour dessiner la grille
// fonction pour charger la grille 
// fonction pour jouer

//TODO : cyclic / aging to work correctly

#include "../include/graphic.h"
#include <X11/keysymdef.h>
#include "../include/grille.h"
#include "../include/jeu.h"
#define SIZEX 1000
#define SIZEY 1000

char show_osc[500];
char text[500];

int aging;
int cyclic;

void grid(cairo_t* current_state, grille *g)
{
    int l = g->nbl;
    int c = g->nbc;
    for(int i = 0; i < l ;i++){
        for(int j = 0 ; j < c;j++){
            double death = 0.1 * g->cellules[i][j]; // degradation of colour used only if mode "aging" is on

            //creation of the grid
            cairo_rectangle(current_state,20 + 80*j,50+80*i,80,80);
		    cairo_set_source_rgb (current_state, 1.0, 1.0, 1.0);
			cairo_stroke(current_state);
    
			if(g->cellules[i][j]>=1 && g->cellules[i][j]<9) //mode standart
            {
				cairo_rectangle(current_state,20 + 80*j,50+80*i,80,80);
				cairo_set_source_rgb (current_state, 0.0, 1.0, 0.0);
				cairo_fill(current_state);
            }
			if(g->cellules[i][j]>=1 && g->cellules[i][j]<9 && aging == 1) // mode viellissement
            {
                cairo_rectangle(current_state,20 + 80*j,50+80*i,80,80);
				cairo_set_source_rgb (current_state, 0.0 + death, 1.0 - death, 0.0);
				cairo_move_to(current_state, 20 + 80*j + 20,50+80*i+50);
                cairo_fill(current_state);
			}
            if (g->cellules[i][j] == -1) // cell non viable
            {
                cairo_rectangle(current_state,20 + 80*j,50+80*i,80,80);
				cairo_set_source_rgb (current_state, 1.0, 0.0, 0.0);
				cairo_fill(current_state);
            }        	
		}
    }
}


void paint(cairo_surface_t *surface, grille *g)
{

    int l = g->nbl;
    int c = g->nbc;
    cairo_t *current_state = cairo_create(surface);
    //background
    cairo_set_source_rgb(current_state, 0.5, 0.5, 0.2);
    cairo_paint(current_state);
    //top-text
    cairo_select_font_face(current_state, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (current_state, 15.0);
    cairo_set_source_rgb (current_state, 1.0, 1.0, 1.0);
    cairo_move_to (current_state, 10.0, 15.0);
    sprintf(text, "Générations: %d"  ,g->generation);
    cairo_show_text(current_state, text);
    cairo_move_to (current_state, 150.0, 15.0);
     sprintf(text, "Aging: %d"  ,aging);
    cairo_show_text(current_state, text);
    cairo_move_to (current_state, 290.0, 15.0);
     sprintf(text, "Cyclic: %d"  ,cyclic);
    cairo_show_text(current_state, text);
    //grid
    grid(current_state, g);
    //memory management, basically free()
    cairo_destroy(current_state);
}

int osc_graph(cairo_surface_t *surface, grille *g){

	cairo_t *current_state = cairo_create(surface);
    cairo_select_font_face(current_state, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(current_state, 15);
    cairo_set_source_rgb(current_state, 1.0, 1.0, 1.0);
    cairo_move_to(current_state, 10, 30);

    int l = g->nbl;
	int c = g->nbc;

	grille gc, gc2;

	alloue_grille(l, c, &gc);
	alloue_grille(l, c, &gc2);

	copie_grille(*g, gc);

	int temps = 0;

	evolue(&gc, &gc2);
	while( testEgal(&gc, &gc2) != 1 && temps < 500 )
	{
			evolue(&gc, &gc2);
			temps++;
	}

    if (temps < 500)
	{
        cairo_show_text(current_state, "Not oscillating\n");
        cairo_move_to(current_state, 10.0, 20.0);
	}
	else
    {
        sprintf(show_osc, "Oscillates over a period : %d \n", temps);
        cairo_show_text(current_state, show_osc);
        cairo_move_to(current_state, 10.0, 20.0);
    }

	return temps;

}


int chargement(cairo_surface_t *surface, Display *dpy, grille *g, grille *gc){
	
    XEvent e;
    cairo_t *current_state = cairo_create(surface);
    cairo_select_font_face(current_state, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(current_state, 15);
    cairo_set_source_rgb(current_state, 1.0, 1.0, 1.0);
    cairo_move_to(current_state, 10, 30);
    cairo_show_text(current_state, "Return to the terminal to continue action!");
    cairo_destroy(current_state);
    XNextEvent(dpy, &e);
    char path[30];
    printf("Enter the path of the file:  ");
    scanf("%s", path);
    while (fileExistsCairo(path) == false){
		printf("The path : %s that you entered does not exist \n", path);
		printf("Enter a new one : ");
		scanf("%s", path);
	}
    printf("New grid in GUI is up and running! \n");
    init_grille_from_file(path, g);
	libere_grille(gc);
	alloue_grille(g->nbl, g->nbc, gc);
}


void debut_jeu(grille *g, grille *gc)
{
    XEvent e;
    Display *dpy;
    Window rootwin;
    Window win;
    int screen;
    int l = g->nbl;
    int c = g->nbc;

    if (!(dpy = XOpenDisplay(NULL)))
    {
        fprintf(stderr, "ERROR : Couldn't open display \n");
        exit(1);
    }

    screen = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, screen);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, screen), BlackPixel(dpy, screen));

    XStoreName(dpy, win, "Jeu de la Vie - Alexandru Dinte");
    XSelectInput(dpy , win, ExposureMask | ButtonPressMask | KeyPressMask);
    
    XMapWindow(dpy, win);
    
    cairo_surface_t *createsurface;
    createsurface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX*l, SIZEY*c);

    while (1 && e.xbutton.button != Button3)
    {
        XNextEvent(dpy , &e);
        if(e.type == Expose && e.xexpose.count<1)
        {
            paint(createsurface, g);
        }
        else if (e.type == ButtonPress)
        {
            if (e.xbutton.button == Button1)
            {
                evolue(g, gc);
                paint(createsurface, g);
                
            }
        }
        else if (e.type == KeyPress)
        {
           if (e.xkey.keycode == XKeysymToKeycode(dpy , XStringToKeysym("C")))
            {
                cyclic = !cyclic;
                paint(createsurface, g);
            }
            if (e.xkey.keycode == XKeysymToKeycode(dpy , XStringToKeysym("V")))
            {
                aging = !aging;
                paint(createsurface, g);
            }
            if (e.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("N")))
            {
                chargement(createsurface, dpy, g, gc);
            }
            if (e.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("O")))
            {
                osc_graph(createsurface, g);
            }

        }
    }
    cairo_surface_destroy(createsurface);
    XCloseDisplay(dpy);

}   
