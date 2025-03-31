CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

SRCS = main.c musique.c
OBJS = $(SRCS:.c=.o)
EXEC = musique

all: $(EXEC)

$(EXEC): $(OBJS)
        $(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

%.o: %.c musique.h
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f $(OBJS) $(EXEC) musique.wav