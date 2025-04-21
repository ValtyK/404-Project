# Nom de l'exécutable
TARGET = main

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =

# Fichiers sources et objets
SRCS = main.c musique.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

# Cible par défaut
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation et génération des dépendances
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

# Nettoyage
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

# Exécuter le programme
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
