CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lm

TARGET = main
SRCS = main.c musique.c
OUTFILE = output.wav

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run: all
	./$(TARGET) $(OUTFILE)

clean:
	rm -f $(TARGET) $(OUTFILE)

.PHONY: all run clean
