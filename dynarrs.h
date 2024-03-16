#ifndef DARRAY_H
#define DARRAY_H

#define BASE_SIZE 4



/***** DYNAMIC 1D ARRAYS *****/
typedef struct {
    unsigned int *elements;
    unsigned int cursize;
    unsigned int maxsize;
} Darray;

Darray* init_Darray(unsigned int length);
void free_Darray(Darray *arr);
void print_Darray(Darray *arr);

//https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d
#define da_append(xs, x)                                                                     \
        do {                                                                                 \
        if ((xs)->cursize == (xs)->maxsize) {                                                \
            if (!(xs)->maxsize) (xs)->maxsize = BASE_SIZE;                                   \
                else (xs)->maxsize *= 2;                                                     \
            (xs)->elements = realloc((xs)->elements, (xs)->maxsize*sizeof(*(xs)->elements)); \
        }                                                                                    \
        (xs)->elements[(xs)->cursize] = x;                                                   \
        (xs)->cursize++;                                                                     \
    } while (0)

#define da_remove(xs, n)    \
    do {                    \
        (xs)->cursize -= n; \
    } while(0)

/***** DYNAMIC 2D ARRAYS *****/
typedef struct {
    Darray *elements;
    unsigned int cursize;
    unsigned int maxsize;
} Dmatrix;

Dmatrix* init_Dmatrix(unsigned int height, unsigned int width);
void free_Dmatrix(Dmatrix *matrix);
void print_Dmatrix(Dmatrix *matrix);

#define dm_set(xs, x0, x1, x)                   \
    do {                                        \
        (xs)->elements[x0].elements[x1] = x;    \
    } while (0)

#define dm_remove(xs, amount)                           \
    do {                                                \
    for (unsigned int index=0; index < amount; index++) \
        free_Darray(&(xs)->elements[(xs)->cursize--]);  \
    } while (0)







#endif /* DARRAY_H */
