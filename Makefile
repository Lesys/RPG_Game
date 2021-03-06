#Les variables automatiques :
#$@ valeur du  target
#$< nom du premier pré-requis associé au target
#$? nom des pré-requis plus récent que le target
#$^ liste sans répétition des pré-requis
#$+ comme $^ mais avec les répétitions
#$* nom du target avec le suffix tronqué

#Variables pour faciliter la saisie et les modifications dans le Makefile :
#Variable pour le compilateur
CC ?= gcc

#Variable où aller chercher les fichiers
VPATH = lib:build:bin:src:include

#Variables pour la confection de la librairie :
#Options pour les lignes de code faites pour la confection des fichiers objets
DIROBJ := bin/
CFLAGS += -fPIC -Wall
OBJETS = character.o error.o
FICHIERSC = $(OBJETS:.o=.c)

#Nom du programme principal
DIRMAIN := src/
PROGRPRINC = main.o
PATHMAIN := $(DIRMAIN)$(PROGRPRINC)

#Noms des librairies statiques et dynamiques
DIRLIB := build/
LINKNAME ?= maBibRPG
libSTATIC := lib$(LINKNAME).a
MAJEUR ?= .1
MINEUR ?= .1
CORRECTION ?= .2
SONAMECOURT := lib$(LINKNAME).so
SONAME := $(SONAMECOURT)$(MAJEUR)
REALNAME := $(SONAME)$(MINEUR)$(CORRECTION)

#Options pour les librairies
libCFLAGS = -shared -fPIC -Wl,-soname,
libLDFLAGS = -L.
libLDLIBS = -lc

#Options pour l'archive
ARFLAGS = rcs

#Options des programmes en statique et dynamique
STATIC = rpg.static
DYNAMIC = rpg.shared
sharedLDFLAGS := -L.
sharedLDLIBS := -l$(LINKNAME)
staticLDFLAGS := -L.
staticLDLIBS := -l:$(libSTATIC)

#Conception du Makefile :
#Execution du programme en entier
all: | MOVE

#Création des dossiers
MKDIR: $(DIRMAIN)$(PROGRPRINC)
	-mkdir $(DIRLIB) $(DIROBJ)

#Fabrication des fichiers objet .o
$(OBJETS): CFLAGS := $(CFLAGS)
$(OBJETS): $(FICHIERSC) MKDIR

#Fabrication du fichier objet main.o
$(PROGRPRINC): LDFLAGS := $(CFLAGS)

#Conception de l'archive pour la bibliothèque statique
$(libSTATIC)($(OBJETS)): ARFLAGS := $(ARFLAGS)
$(libSTATIC)($(OBJETS)): $(OBJETS)

#Règle pour appeler la conception de l'archive
$(libSTATIC): $(libSTATIC)($(OBJETS))

#Conception de la bibliothèque dynamique avec ses 2 liens symboliques
$(REALNAME): $(OBJETS)
	$(CC) $(libCFLAGS)$(SONAME) -o $@ $^
	ln -sf $@ $(SONAMECOURT)
	ln -sf $@ $(SONAME)

#Génération du programme static
$(STATIC): LDFLAGS := $(staticLDFLAGS)
$(STATIC): LDLIBS := $(staticLDLIBS)
$(STATIC): $(DIRMAIN)$(PROGRPRINC) $(libSTATIC)
	$(CC) -o $@ $(DIRMAIN)$(PROGRPRINC) $(staticLDFLAGS) $(staticLDLIBS)

#Génération du programme dynamique
$(DYNAMIC): LDFLAGS := $(sharedLDFLAGS)
$(DYNAMIC): LDLIBS := $(sharedLDLIBS)
$(DYNAMIC): $(DIRMAIN)$(PROGRPRINC) $(REALNAME)
	$(CC) -o $@ $(DIRMAIN)$(PROGRPRINC) $(sharedLDFLAGS) $(sharedLDLIBS)

#Execution du programme dynamique
execution: $(DYNAMIC) MOVE clearScreen
	-LD_LIBRARY_PATH=./$(DIRLIB):$LD_LIBRARY_PATH ./$(DIRLIB)$(DYNAMIC)

#Move les fichiers dans leur dossier respectif : .so .a et executable dans le dossier build. .o dans le dossier bin
MOVE: $(DYNAMIC) $(STATIC)
	-mv *maBib* *rpg* ./$(DIRLIB)
	-mv $(DIRMAIN)*.o $(DIRLIB)*.o *.o ./$(DIROBJ)

#Nettoie les fichiers créés dans le current directory
clean: cleanNewDir
	-rm *.o *maBib* *rpg*

#Nettoie les dossiers créés et leur contenu
cleanNewDir:
	-rm -R $(DIRLIB) $(DIROBJ)

#Nettoie l'écran
clearScreen: 
	-clear