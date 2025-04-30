CC = gcc

# Options de compil :
# -Wall      : avertissements courants
# -Wextra    : avertissements supplémentaires
# -O2        : Opti du code pour meilleures perf
CFLAGS = -Wall -Wextra -O2 -g
# Biblio à lier (math.h nécessite -lm)
LDFLAGS = -lm

# differents chemin des fichiers
LEX_PATH = lexique
SYNT_PATH = syntaxe
ARB_PATH = arbre/ast
WAV_PATH = wav
LIB_PATH = lib
 

# variable pour FLEX
LEX = $(LEX_PATH)/analyse_lexicale

# variable pour TS
TS = $(TS_PATH)/Table_symbole

# variable pour FSYNT
SYNT = $(SYNT_PATH)/analyse_syntaxique

# variable pour ARBC
ARBC = $(ARB_PATH)_construction
ARBP = $(ARB_PATH)_parcours

# variable pour la librairie musique
LIB = $(LIB_PATH)/musique

# fichiers sources
SRCS = melodie.c $(LEX).c $(SYNT).c $(LIB).c $(ARBC).c $(ARBP).c

# liste des fichiers objets en remplacant .c par .o
OBJS = $(SRCS:.c=.o)


# Nom de l'executable final
EXEC = melodie


# créer l'executable
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)


# Regle principale : compilation du programme
all: $(EXEC) 

# crée le .c d'analyse lexicale
$(LEX).c: $(LEX).l 
	flex -o $@ $<

# compiler chaque fichier .c en .o
# (générique et s'applique à tous les fichiers sources)
%.o: %.c
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@

test_lexeme: $(LEX).o test/test_lexeme.o
	$(CC) -o $@ $^

test_syntaxe: $(LEX).o $(SYNT).o $(ARBC).o $(ARBP).o test/test_syntaxe.o lib/musique.o
	$(CC) $(LDFLAGS) -o $@ $^

TStest: table_symboles/test_TS.o table_symboles/table_symboles.o
	$(CC) $(CFLAGS) -o $@ $^

# nettoyer les fichiers générés (executable, objets, fichier WAV)
clean:
	rm -f *.wav $(OBJS) $(EXEC) $(LEX).c test_lexeme test_syntaxe TStest
