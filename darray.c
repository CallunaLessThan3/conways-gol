#include "dynarrs.h"
#include <stdio.h>
#include <stdlib.h>


Darray* init_Darray(unsigned int length) {
    Darray *arr = malloc(sizeof(Darray));
    for (unsigned int i=0; i < length; i++) {
        da_append(arr, 0);
    }
    return arr;
}


void free_Darray(Darray *arr) {
    free(arr->elements);
}


void print_Darray(Darray *arr) {
        //printf("Elements: {");
        printf("{");
        for (unsigned int index=0; index < arr->cursize; index++)
            printf("%d,", arr->elements[index]);
        printf("}\n");
        //printf("Current Size: %d\n", arr->cursize);
        //printf("Max Size: %d\n", arr->maxsize);
}

