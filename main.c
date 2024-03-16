#include "main.h"
#include "dynarrs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>


int matrix[HEIGHT][WIDTH];

void generate_random_matrix(Dmatrix *matrix) {
    for (int y=0; y < matrix->cursize; y++) {
        for (int x=0; x < matrix->elements[0].cursize; x++) {
            unsigned int val = rand() % 2;
            dm_set(matrix, y, x, val);
        }
    }
}


// TESTING ONLY
void print_matrix_values() {
    for (int y=0; y < HEIGHT; y++) {
        for (int x=0; x < WIDTH; x++) {
            printf("%d", matrix[y][x]);
        }
        printf("\n");
    }
}


// TESTING ONLY
void display_matrix() {
    for (int y=0; y < HEIGHT; y++) {
        for (int x=0; x < WIDTH; x++) {

            // alternative is indexing into char[] that contains values
            char pixel;
            if (matrix[y][x]) {
                pixel = '#';
            } else {
                pixel = ' ';
            }
            printf("%c", pixel);
        }
        printf("\n");
    }
}


int wrap_num(int num, int maxsize) {
    return ((num % maxsize)+maxsize)%maxsize;
}


// this feels wrong but i dont know ^-^
int count_neighbors(Dmatrix *matrix, unsigned int ypos, unsigned int xpos) {
    unsigned int neighbors = 0;
    for (int y=-1; y <= 1; y++) {
        for (int x=-1; x <= 1; x++) {
            int yw = wrap_num(ypos+y, matrix->cursize);
            int xw = wrap_num(xpos+x, matrix->elements[0].cursize);
            if (matrix->elements[yw].elements[xw]) {
                neighbors++;
            }
        }
    }

    if (matrix->elements[ypos].elements[xpos]) neighbors--;
    return neighbors;
}


/* RULES:
    - Each live cell with < 2 neighbors die
    - Each live cell with 2-3 neighbors live
    - Each live cell with > 3 neighbors die
    - Each dead cell with = 3 neighbors live
*/
Dmatrix* iterate_matrix(Dmatrix *matrix) {
    Dmatrix *step = init_Dmatrix(matrix->cursize, matrix->elements[0].cursize);
    for (int y=0; y < matrix->cursize; y++) {
        for (int x=0; x < matrix->elements[0].cursize; x++) {
            unsigned int neighbors = count_neighbors(matrix, y, x);
            unsigned int val = 0;
            if (matrix->elements[y].elements[x]) {
                if (neighbors == 2 || neighbors == 3) val = 1;
            } else {
                if (neighbors == 3) (val = 1);
            }
            dm_set(step, y, x, val);
        }
    }
    free_Dmatrix(matrix);
    return step;
}


// TODO: put rendering in a separate file
void add_rectangle(int xpos, int ypos) {
    unsigned int ax = (xpos / SCALE);
    unsigned int ay = (ypos / SCALE);
    (matrix[ay][ax]) ? (matrix[ay][ax] = 0) : (matrix[ay][ax] = 1);
}


void draw_frame() {
    for (int y=0; y < HEIGHT; y++) {
        for (int x=0; x < WIDTH; x++) {
            unsigned int boxsize = SCALE;
            unsigned int xpos = x*boxsize;
            unsigned int ypos = y*boxsize;
            if (matrix[y][x]) {
                DrawRectangle(xpos, ypos, boxsize, boxsize, GRAY);
            }
        }
    }
}


int state = 0;
void check_key_pressed() {
    //todo: extract this
    if (IsKeyPressed('R')) {
        state = 1;
    }
    else if (IsKeyPressed('E')) {
        state = 0;
    }
    else if (IsKeyPressed('G')) {
        state = 0;
        //generate_random_matrix();
    }
    else if (IsKeyPressed('N') && state == 0) {
        //iterate_matrix();
    }
    else if (IsKeyPressed('C')) {
    int empty[HEIGHT][WIDTH] = {0};
        memcpy(matrix, empty, sizeof(matrix));
        state = 0;
    }
    else if (IsKeyPressed('S')) {
        //TODO: save_matrix(matrix);
    }
}


/*
STATES
    0: Editing
    1: Running
*/
void start() {
    const unsigned int WINDOW_HEIGHT = HEIGHT*SCALE;
    const unsigned int WINDOW_WIDTH = WIDTH*SCALE;
    const unsigned int FPS = 15;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game Of Life");
    SetTargetFPS(FPS);
    SetExitKey('Q');

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            check_key_pressed();
            draw_frame();

            DrawText("Keybinds: " , 0, 20, 20, BLACK);
            DrawText("R: Run" , 0, 40, 20, BLACK);
            DrawText("E: Edit" , 0, 60, 20, BLACK);
            DrawText("G: Generate Random" , 0, 80, 20, BLACK);

            // can do if(state) but less readable ..
            switch (state) {
                case 0: //Editing
                    DrawText("State: Editing" , 0, 0, 20, BLACK);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) add_rectangle(GetMouseX(), GetMouseY());
                    break;
                case 1: //Running
                    DrawText("State: Running" , 0, 0, 20, BLACK);
                    //iterate_matrix();
                    break;
                default:
                    exit(1);
            }


        EndDrawing();
    }
    CloseWindow();
}

/***** DYNAMIC MATRIX TESTING *****/




int main() {
    srand(time(0));

    Dmatrix *mtx = init_Dmatrix(10, 10);

    dm_set(mtx, 0, 1, 1);
    dm_set(mtx, 1, 2, 1);
    dm_set(mtx, 2, 0, 1);
    dm_set(mtx, 2, 1, 1);
    dm_set(mtx, 2, 2, 1);
    print_Dmatrix(mtx);

    mtx = iterate_matrix(mtx);
    printf("----------\n");
    print_Dmatrix(mtx);

    mtx = iterate_matrix(mtx);
    printf("----------\n");
    print_Dmatrix(mtx);


    return 0;
}
