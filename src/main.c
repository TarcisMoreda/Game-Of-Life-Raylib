#include "../include/game.h"

int main(int argc, char const *argv[]){
    //Definindo constantes que podem ser alteradas para uma experiencia diferente
    const int win_width = 800;
    const int win_height = 600;
    const int cell_size = 8;
    const int cols = (int) win_width/cell_size;
    const int rows = (int) ((win_height-50)/cell_size);
    const int fps = 60;
    const int generations_per_sec = 6;
    const int frames_per_generation = fps/generations_per_sec;

    //Alocando toda a memoria nescessaria para o jogo funcionar
    cell** board = create_board(rows, cols, win_width, win_height, cell_size);
    int** aux_board = create_aux_board(rows, cols, win_width, win_height, cell_size);

    //Variaveis para a logica do jogo
    bool game_state = false;
    int current_frame = 0;
    char str_buffer[50];
    int generation = 0;

    //Criando os botoes
    Rectangle start_button;
    start_button.x = 0;
    start_button.y = rows*cell_size;
    start_button.width = 200;
    start_button.height = win_height;
    Rectangle clear_button;
    clear_button.x = win_width-200;
    clear_button.y = rows*cell_size;
    clear_button.width = 200;
    clear_button.height = win_height;

    //Iniciando a janela e configurando
    InitWindow(win_width, win_height, "Conway's Game of Life");
    SetTargetFPS(fps);

    //Loop principal do jogo
    while (!WindowShouldClose()){
        click_state(board, rows, cols, game_state);

        //Logica dos botoes
        if (CheckCollisionPointRec(GetMousePosition(), start_button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        game_state = !game_state;
        if (CheckCollisionPointRec(GetMousePosition(), clear_button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_state){
            reset_board(board, rows, cols);
            generation = 0;
        }

        //Condicao para a proxima geracao
        if (current_frame%frames_per_generation == 0 && game_state){
            game_step(board, aux_board, rows, cols, win_width, win_height, cell_size);
            ++generation;
        }

        //Concatenando str das geracoes
        snprintf(str_buffer, 50, "Geracao: %d", generation);

        BeginDrawing();
        ClearBackground(GRAY);

        show_board(board, rows, cols, win_width, cell_size);

        //Logica para a mudanca de cor e texto do botao start_button
        if (!game_state) {
            DrawRectangleRec(start_button, LIME);
            DrawText("Iniciar", start_button.x+10, start_button.y+5, win_height-start_button.y, WHITE);
            }
        else{
            DrawRectangleRec(start_button, RED);
            DrawText("Parar", start_button.x+10, start_button.y+5, win_height-start_button.y, WHITE);
            }

        DrawRectangleRec(clear_button, BROWN);
        DrawText("Limpar", clear_button.x+20, clear_button.y+5, win_height-clear_button.y, WHITE);

        DrawText(str_buffer, start_button.width+10, start_button.y+5, win_height-clear_button.y, WHITE);

        EndDrawing();
        if (game_state) ++current_frame;
    }

    //Limpando memoria e finalizando raylib
    clear_aux_board_memory(aux_board, rows);
    clear_board_memory(board, cols);
    CloseWindow();

    return 0;
}
