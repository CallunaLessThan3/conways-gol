#ifndef CGOL_H
#define CGOL_H

// size of rectangles in pixels
#define SCALE 100
#define HEIGHT 10
#define WIDTH 20

void save_matrix(int (*matrix)[HEIGHT][WIDTH]);
int** load_matrix();

#endif /* CGOL_H */
