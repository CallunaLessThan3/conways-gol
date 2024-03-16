#include "dynarrs.h"
#include <stdlib.h>


Dmatrix* init_Dmatrix(unsigned int height, unsigned int width) {
    Dmatrix *matrix = malloc(sizeof(Dmatrix));
    for (unsigned int i=0; i < height; i++) {
        Darray *LL = init_Darray(width);
        da_append(matrix, *LL);
    }
    return matrix;
}


void free_Dmatrix(Dmatrix *matrix) {
    for (unsigned int i=0; i < matrix->cursize; i++) {
        free_Darray(&matrix->elements[i]);
    }
    free(matrix);
}


void print_Dmatrix(Dmatrix *matrix) {
    for (unsigned int i=0; i < matrix->cursize; i++) {
        print_Darray(&matrix->elements[i]);
    }
}
