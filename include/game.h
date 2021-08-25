#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

enum{alive = 1, dead = 0};
typedef struct cell cell;

cell** create_board(int rows, int cols, int width, int height, int cell_size);
int** create_temp_board(int rows, int cols, int width, int height, int cell_size);
int check_neighbours(cell** board, int rows, int cols, int x, int y);
int game_step(cell** board, int rows, int cols, int width, int height, int cell_size);
int show_board(cell** board, int rows, int cols, int width, int cell_size);
int reset_board(cell** board, int rows, int cols);
int click_state(cell** board, int rows, int cols, bool game_state);
int clear_board_memory(cell** board, int rows);
int clear_temp_board_memory(int** board, int rows);