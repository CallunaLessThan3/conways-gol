CC     = gcc
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -g
DEPS   = main.h dynarrs.h
OBJ    = main.o fileio.o darray.o dmatrix.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o main

