#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>


#define SCALE 10 // size of rectangles in pixels
#define HEIGHT 175 
#define WIDTH 100

int matrix[HEIGHT][WIDTH] = {0};

void generate_random_matrix() {
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {
            matrix[x][y] = rand() % 2;
        }
    }
}


// unused
void print_matrix_values() {
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {
            printf("%d", matrix[x][y]);
        }
        printf("\n");
    }
}


// unused
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
    unsigned int neighbors = 0;
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
    int step[HEIGHT][WIDTH] = {0};
    for (int i=0; i < HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++) {
            unsigned int neighbors = count_neighbors(i, j);
            if (matrix[i][j]) {
                if (neighbors == 2 || neighbors == 3) step[i][j] = 1;
                else step[i][j] = 0;
            } else {
                if (neighbors == 3) step[i][j] = 1;
            }

        }
    }
    // might need to malloc step --> free step, unsure if this is a memory leak
    memcpy(matrix, step, sizeof(matrix));
}


void draw_frame() {
    for (int x=0; x < HEIGHT; x++) {
        for (int y=0; y < WIDTH; y++) {
            unsigned int boxsize = SCALE;
            unsigned int xpos = x*boxsize;
            unsigned int ypos = y*boxsize;
            if (matrix[x][y]) {
                DrawRectangle(xpos, ypos, boxsize, boxsize, GRAY);
            }
        }
    }
}


void add_rectangle(int xpos, int ypos) {
    unsigned int ax = (xpos / SCALE);
    unsigned int ay = (ypos / SCALE);
    (matrix[ax][ay]) ? (matrix[ax][ay] = 0) : (matrix[ax][ay] = 1);
}


/*
STATE KEY
    0: Editing
    1: Running
*/
int state = 0;

void start() {
    //swapped bc i used syntax of [height][width] to be more similar to matrices
    const unsigned int WINDOW_HEIGHT = WIDTH*SCALE;
    const unsigned int WINDOW_WIDTH = HEIGHT*SCALE;
    const unsigned int FPS = 15;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "C-gol");
    SetTargetFPS(FPS);
    SetExitKey('Q');

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (IsKeyPressed('R')) {
                state = 1;
            }
            if (IsKeyPressed('E')) {
                state = 0;
            }
            if (IsKeyPressed('G')) {
                state = 0;
                generate_random_matrix();
            }


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
                    iterate_matrix();
                    break;
                default:
                    exit(1);
            }


        EndDrawing();
    }
    CloseWindow();
}


int main() {
    srand(time(0));
    start();
    return 0;
}
