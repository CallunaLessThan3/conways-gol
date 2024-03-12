CC=gcc
CFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
DEPS=main.h
OBJ = main.o fileio.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o

