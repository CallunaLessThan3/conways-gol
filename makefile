CC=gcc
RLFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

c-gol:
	$(CC) -o main c-gol.c $(RLFLAGS)

clean:
	rm -rf main
