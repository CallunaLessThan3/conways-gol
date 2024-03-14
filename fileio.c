#include "main.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


// accepting pointer to matrix bc i want to move away from global variable matrix
void save_matrix(int (*matrix)[HEIGHT][WIDTH]) {
    char filename[8] = "awa.bin";
    FILE *out_file = fopen(filename, "w");
    assert(out_file != NULL);

    for (int y=0; y < HEIGHT; y++) {
        for (int x=0; x < WIDTH; x++) {
            fprintf(out_file, "%d", (*matrix)[y][x]);
        }
        fprintf(out_file, " ");
    }
    fclose(out_file);
}


// idk how to do this lol
int** load_matrix() {
    int** test = malloc(HEIGHT*HEIGHT*sizeof(int));
    return test;
}
