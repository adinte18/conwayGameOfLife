CC = gcc -g
EXEC = libs main doc dist clean
SOURCE = src/grille.c src/main.c src/jeu.c src/io.c src/graphic.c
INCLUDE = include/jeu.h include/grille.h include/graphic.h include/io.h
OBJECTDIR = obj/
BINDIR = bin/
OBJECTS = main.o grille.o jeu.o
VERSION = $(shell git describe --tags)
GRILLES = grilles/$(wildcard *.txt)
DOC = doxygen Doxyfile
MAKEDIST = tar -c -lzma -f DinteAlexandru-GoL-$(VERSION).tar.xz $(SOURCE) $(INCLUDE) Makefile Doxyfile $(GRILLES)*.txt *.md
IFLAGS = -I.. -I/usr/include/cairo/
LDFLAGS = 
MODE = 
LIB = libjeu.a
LIBDIR = lib/
LIBOBJ = main.o jeu.o grille.o
MAKELIB = ar rcs libjeu.a obj/main.o obj/jeu.o obj/grille.o 
LBFLAGS = 
vpath %.c src/
vpath %.h include/

ifeq ($(MODE),TEXTE)
	LIBOBJ += io.o
	MAKELIB += obj/io.o
	LBFLAGS = -L. 
else 
	LDFLAGS = -lcairo -lm -lX11 -Llib
	LIBOBJ += graphic.o
	MAKELIB += obj/graphic.o
	LBFLAGS = -L. -ljeu
endif

all: $(EXEC)

main: $(LIB) $(INCLUDE)
	$(CC) $(IFLAGS) -o main $(LIBDIR)$(LIB) $(LDFLAGS) $(LBFLAGS) -lpthread
	mkdir -p $(BINDIR)
	mv $@ $(BINDIR)

%.o : %.c 
	$(CC) -c $< $(IFLAGS) $(LDFLAGS)
	mkdir -p $(OBJECTDIR)
	mv *.o $(OBJECTDIR)


libjeu.a: $(LIBOBJ)
	$(MAKELIB)

libs: libjeu.a
	mkdir -p $(LIBDIR)
	mv *.a $(LIBDIR)

dist:
	$(MAKEDIST)

doc:
	$(DOC)

clean:
	rm -rf $(OBJECTDIR)


