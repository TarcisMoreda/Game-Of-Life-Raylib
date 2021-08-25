#include "../include/game.h"

struct cell{
    Rectangle rect;
    int state;
};

cell** create_board(int rows, int cols, int width, int height, int cell_size){
    cell** board = NULL;
    board = (cell**) malloc(sizeof(cell*)*cols);
    for (int i=0; i<cols; i++) board[i] = (cell*) malloc(sizeof(cell)*rows);

    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            board[x][y].rect.x = cell_size/2 + cell_size*x;
            board[x][y].rect.y = cell_size/2 + cell_size*y;
            board[x][y].rect.width = cell_size;
            board[x][y].rect.height = cell_size;
            board[x][y].state = dead;
        }
    }

    return board;
}

int** create_temp_board(int rows, int cols, int width, int height, int cell_size){
    int** board = NULL;
    board = (int**) malloc(sizeof(int*)*rows);
    for (int i=0; i<cols; i++) board[i] = (int*) malloc(sizeof(int)*rows);

    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y] = dead;

    return board;
}

int check_neighbours(cell** board, int rows, int cols, int x, int y){
    int neighbours = 0;
    
    for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
            if (i == 0 && j == 0) continue;
            if (x+i == -1 || y+j == -1) continue;
            if (x+i == cols || y+j == rows) continue;
            if (board[x+i][y+j].state == alive) neighbours++;
        }
    }

    return neighbours;
}

int game_step(cell** board, int rows, int cols, int width, int height, int cell_size){
    if (board == NULL) return 0;

    int neighbours;
    int temp;
    int** temp_board = create_temp_board(rows, cols, width, height, cell_size);
    
    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    temp_board[x][y] = board[x][y].state;
    
    
    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            neighbours = check_neighbours(board, rows, cols, x, y);

            if (board[x][y].state == alive && (neighbours < 2 ||  neighbours > 3)) temp_board[x][y] = dead;
            if (board[x][y].state == dead && neighbours == 3) temp_board[x][y] = alive;
        }
    }
    
    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y].state = temp_board[x][y];
    
    clear_temp_board_memory(temp_board, cols);
    return 1;
}

int show_board(cell** board, int rows, int cols, int width, int cell_size){
    if (board == NULL) return 0;

    Color temp_color;

    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            if (board[x][y].state == alive) temp_color = WHITE;
            else if (board[x][y].state == dead) temp_color = BLACK;
            DrawRectanglePro(board[x][y].rect, (Vector2){board[x][y].rect.width/2, board[x][y].rect.height/2}, 0.0, temp_color);
            DrawLine(0, y*cell_size, width, y*cell_size, GRAY);
        }
        DrawLine(x*cell_size, 0, x*cell_size, rows*cell_size, GRAY);
    }

    return 1;
}

int click_state(cell** board, int rows, int cols, bool game_state){
    if (board == NULL) return 0;

    for (int x=0; x<cols; x++) 
    for (int y=0; y<rows; y++)
    if (CheckCollisionPointRec(GetMousePosition(), board[x][y].rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_state)
    board[x][y].state = !board[x][y].state;

    return 1;
}

int reset_board(cell** board, int rows, int cols){
    if (board == NULL) return 0;

    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y].state = dead;

    return 1;
}

int clear_board_memory(cell** board, int cols){
    if (board == NULL) return 0;
    
    for (int i=0; i<cols; i++) free(board[i]);
    free(board);

    return 1;
}

int clear_temp_board_memory(int** board, int cols){
    if (board == NULL) return 0;
    
    for (int i=0; i<cols; i++) free(board[i]);
    free(board);

    return 1;
}