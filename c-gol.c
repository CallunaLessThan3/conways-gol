#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

/*
 

OUTLINE:
    Represented by nxn matrix, where '#' is a living cell, and ' ' is a dead cell 
*/

#define SIZE 50
#define HEIGHT SIZE
#define WIDTH SIZE

int matrix[HEIGHT][WIDTH];



void init_matrix() {
    srand(time(NULL));
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {
            matrix[x][y] = rand() % 2;
        }
    }
}


void print_matrix_values() {
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {
            printf("%d", matrix[x][y]);
        }
        printf("\n");
    }
}


void display_matrix() {
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {

            // alternative is indexing into char[] that contains values
            char pixel;
            if (matrix[x][y]) {
                pixel = '#';
            } else {
                pixel = ' ';
            }
            printf("%c", pixel);
        }
        printf("\n");
    }
}


int wrap_num(int x, int size) {
    return ((x % size)+size)%size;
}


int count_neighbors(int x, int y) {
    int neighbors = 0;
    for (int i=-1; i <= 1; i++) {
        for (int j=-1; j <= 1; j++) {
            int xpos = wrap_num(x+i, WIDTH);
            int ypos = wrap_num(y+j, HEIGHT);
            if (matrix[xpos][ypos]) {
                neighbors++;
            }
        }
    }

    if (matrix[x][y]) neighbors--;
    return neighbors;
}


/* RULES:
    - Each live cell with < 2 neighbors die
    - Each live cell with 2-3 neighbors live
    - Each live cell with > 3 neighbors die
    - Each dead cell with = 3 neighbors live
*/
void iterate_matrix() {
    int step[HEIGHT][WIDTH];
    for (int i=0; i < HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++) {
            int neighbors = count_neighbors(i, j);
            if (matrix[i][j]) {
                if (neighbors < 2 || neighbors > 3) step[i][j] = 0;
            } else {
                if (neighbors == 3) step[i][j] = 1;
            }

        }
    }
    // might need to malloc step --> free step, unsure if this is a memory leak
    memcpy(matrix, step, sizeof(matrix));
}


int main() {
    init_matrix();

    char input;
    for (;;) {
        printf("input: ");
        scanf("%c", &input);
        if (input == 'q') break;
        if (input == '\n') {
            iterate_matrix();
            display_matrix();
        }
    }
    return 0;
}
