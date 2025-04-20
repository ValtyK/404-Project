CC = gcc

# Options de compil :
# -Wall      : avertissements courants
# -Wextra    : avertissements supplémentaires
# -O2        : Opti du code pour meilleures perf
CFLAGS = -Wall -Wextra -O2

# Biblio à lier (math.h nécessite -lm)
LDFLAGS = -lm

# differents chemin des fichiers
LEX_PATH = lexique
WAV_PATH = wav

# variable pour FLEX
LEX = $(LEX_PATH)/analyse_lexicale

# fichiers sources
SRCS = $(LEX).c main.c musique.c test_lexeme.c

# liste des fichiers objets en remplacant .c par .o
OBJS = $(SRCS:.c=.o)


# Nom de l'executable final
EXEC = musique 

# Regle principale : compilation du programme
all: $(LEX).c $(EXEC)

# créer l'executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

# crée le .c d'analyse lexicale
$(LEX).c: $(LEX).l 
	flex -o $@ $<

# compiler chaque fichier .c en .o
# (générique et s'applique à tous les fichiers sources)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test_lexeme: lexique/analyse_lexicale.o test_lexeme.o
	$(CC) -o $@ $^ 

# nettoyer les fichiers générés (executable, objets, fichier WAV)
clean:
	rm -f $(OBJS) $(EXEC) $(LEX).c musique.wav test_lexeme
