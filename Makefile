CC = gcc

# Options de compil :
# -Wall      : avertissements courants
# -Wextra    : avertissements supplémentaires
# -O2        : Opti du code pour meilleures perf
CFLAGS = -Wall -Wextra -O2

# Biblio à lier (math.h nécessite -lm)
LDFLAGS = -lm

# variable pour FLEX
LEX = analyse_lexicale

# fichiers sources
SRCS = analyse_lexicale.c main.c musique.c

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

# nettoyer les fichiers générés (executable, objets, fichier WAV)
clean:
	rm -f $(OBJS) $(EXEC) $(LEX).c musique.wav
