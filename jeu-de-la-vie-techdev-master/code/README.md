
# Game of Life

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input

## Execution

Use **`make`**  to compile the project. 

In order to clear the temporary files use  **`make clean`** . 

If you would like to create an archive of the project, with the  **`.tar.xz`**  extension please use **`make dist`** . 

Also, in order to automatically generate the documentation of my project, feel free to use **`make doc`** . 

You can create the executable in 2 modes **`TEXTE`** and **`GRAPHIC`**. By default graphical mode is created by **`make`**. Use  **`make MODE=TEXTE`** to compile in `TEXTE` mode

## Running
[image]: https://i.imgur.com/mLOoFpw.png
After successfully compiling the project , you need to start it by typing : 
```
./main grilles/grille#.txt
```
Where `'#'` stands for the number of the file you want to open. There are up to 8 files of `.txt` format.

If the program started without errors this is what you would normally see : 
![alt text][image] 
Starting from the top side of the image you can see a table consisting of 3 variables : `Generations` , `Cyclic mode` and `Aging`. All 3 of the variables that you can see on the image, can change depending on what keys you are pressing on your keyboard. By pressing the key `Enter` , the value of `Generations`increases by 1. By pressing `v` on your keyboard, you can toggle off the aging of a cell, and by pressing `c` on your keyboard you can switch between cyclic and non-cyclic mode of calculation. Each user has a menu of avaliable instructions that he can use in order to modify the execution of the program. 
## Versions

### v. 1.0 :
  - Added `alloue_grille()` and `libere_grille()` functions
  - Added input action

### v. 1.1 :
  - Updated `alloue_grille()`
  - Updated io.c. Optimized `affiche_grille()` for a cleaner terminal. Added some text to support the user.

### v. 2.0
#### Modifications
 - Modified `compte_voisins_vivantes()`. It now counts the living neighbours in 2 modes : **`cyclique`** and **`non_cyclique`** 
 - Modified `affiche_ligne`
 #### New features 
 - Added `show_mode()` and `show_aging()` in order to print the aging and the state of cyclic mode
 -  `show_menu()` was added in order to print the menu of keyboard input instructions avaliable to the user 
 - Added `incremente()`. The function increments the value of a cell , only if it is alive
 - Added more keyboard input actions. Now you can press the key `v` on your keyboard in order to toggle on and off the aging of a cell. Added the key `c` to switch from cycled calculation to non-cycled.
 - Documented the functions
 #### Misc
 - `Makefile` update

### v. 2.1
#### New features
- Added `fileExists()` that checks if a file exists based on a given path.


### v.2.2
#### Misc
 - `Makefile` update

### v3.0
 - `set_non_viable` and `make_non_viable` added.
 -  `Makefile` update

### v4.0
#### Cairo implementation
#### New features
 - With the graphic library Cairo, I implemented the graphical representation of the project. A new file `graphic.c` aswel as `graphic.h`. 
 - Added the following functions: `grid` `paint` `chargement` `debut_jeu` for the graphical representation of the project.
 - Added `aging` and `cyclic` modes for the Cairo representation.
 - A little `Makefile` update that helps compile the executable in 2 modes `TEXT` and `GRAPHIC`
### v5.0
#### New features
 - Added `oscilation` and `osc_graph` that tests if a grid is oscilating or not
 - `Makefile` update. Added lib dependency for the executable