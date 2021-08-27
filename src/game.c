#include "../include/game.h"
#include <stdlib.h>

//definindo o que e uma celula
enum{alive = 1, dead = 0};
struct cell{
    Rectangle rect;
    int state;
};

//Funcao aloca memoria para o tabuleiro e preenche os dados de acordo
cell** create_board(int rows, int cols, int width, int height, int cell_size){
    cell** board = NULL;
    board = (cell**) malloc(sizeof(cell*)*cols);
    for (int x=0; x<cols; x++) board[x] = (cell*) malloc(sizeof(cell)*rows);

    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            board[x][y].rect.x = cell_size*x;
            board[x][y].rect.y = cell_size*y;
            board[x][y].rect.width = cell_size;
            board[x][y].rect.height = cell_size;
            board[x][y].state = dead;
        }
    }

    return board;
}

//Funcao aloca memoria para o tabuleiro auxiliar e preenche os dados
int** create_aux_board(int rows, int cols, int width, int height, int cell_size){
    int** board = NULL;
    board = (int**) malloc(sizeof(int*)*cols);
    for (int x=0; x<cols; x++) board[x] = (int*) malloc(sizeof(int)*rows);

    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y] = dead;

    return board;
}

//Procura por todos os vizinhos da celula atual
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

//Faz a proxima geracao do jogo
int game_step(cell** board, int** aux_board, int rows, int cols, int width, int height, int cell_size){
    if (board == NULL) return 0;

    int neighbours;
    int temp;
    
    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    aux_board[x][y] = board[x][y].state;
    
    
    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++){
        neighbours = check_neighbours(board, rows, cols, x, y);
        
        if (board[x][y].state == alive && (neighbours < 2 ||  neighbours > 3)) aux_board[x][y] = dead;
        if (board[x][y].state == dead && neighbours == 3) aux_board[x][y] = alive;
    }
    
    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y].state = aux_board[x][y];

    reset_aux_board(aux_board, rows, cols);

    return 1;
}

//Desenha o tabuleiro na tela
int show_board(cell** board, int rows, int cols, int width, int cell_size){
    if (board == NULL) return 0;

    Color temp_color;

    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            if (board[x][y].state == alive) temp_color = WHITE;
            else if (board[x][y].state == dead) temp_color = BLACK;
            DrawRectangleRec(board[x][y].rect, temp_color);
            DrawLine(0, y*cell_size, width, y*cell_size, GRAY);
        }
        DrawLine(x*cell_size, 0, x*cell_size, rows*cell_size, GRAY);
    }

    return 1;
}

//Checa por click em celula do tabuleiro e muda seu estado
int click_state(cell** board, int rows, int cols, bool game_state){
    if (board == NULL) return 0;

    for (int x=0; x<cols; x++) 
    for (int y=0; y<rows; y++)
    if (CheckCollisionPointRec(GetMousePosition(), board[x][y].rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_state)
    board[x][y].state = !board[x][y].state;

    return 1;
}

//Reseta o estado de todas as celulas para morta
int reset_board(cell** board, int rows, int cols){
    if (board == NULL) return 0;

    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y].state = dead;

    return 1;
}

//Reseta o estado de todas as celulas do auxiliar para morta
int reset_aux_board(int** board, int rows, int cols){
    if (board == NULL) return 0;

    for (int x=0; x<cols; x++)
    for (int y=0; y<rows; y++)
    board[x][y] = dead;

    return 1;
}

//Limpa a memoria do tabuleiro
int clear_board_memory(cell** board, int cols){
    if (board == NULL) return 0;
    
    for (int x=0; x<cols; x++) free(board[x]);
    free(board);

    return 1;
}

//Limpa a memoria do auxiliar
int clear_aux_board_memory(int** board, int cols){
    if (board == NULL) return 0;
    
    for (int x=0; x<cols; x++) free(board[x]);
    free(board);

    return 1;
}