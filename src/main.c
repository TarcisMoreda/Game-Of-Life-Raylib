#include "../include/game.h"

int main(int argc, char const *argv[]){
    const int win_width = 800;
    const int win_height = 600;
    const int cell_size = 16;
    const int rows = (int) win_width/cell_size;
    const int cols = (int) ((win_height-(3*16))/cell_size);
    const int fps = 60;
    const int frames_per_generation = fps/2;

    cell** board = create_board(rows, cols, win_width, win_height, cell_size);
    Color temp_color;
    bool game_state = false;
    int current_frame = 0;

    InitWindow(win_width, win_height, "Conway's Game of Life");
    SetTargetFPS(fps);

    Rectangle start_button;
    start_button.x = 0;
    start_button.y = cols*cell_size;
    start_button.width = 200;
    start_button.height = win_height-(cols*cell_size);

    while (!WindowShouldClose()){
        for (int x=0; x<rows; x++) 
        for (int y=0; y<cols; y++)
        if (CheckCollisionPointRec(GetMousePosition(), board[x][y].rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_state)
        board[x][y].state = !board[x][y].state;

        if (CheckCollisionPointRec(GetMousePosition(), start_button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        game_state = !game_state;

        if (current_frame%frames_per_generation == 0 && game_state)
        game_step(board, rows, cols, win_width, win_height, cell_size);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        for (int x=0; x<rows; x++) 
        for (int y=0; y<cols; y++){
            if (board[x][y].state == alive) temp_color = WHITE;
            else if (board[x][y].state == dead) temp_color = BLACK;
            DrawRectanglePro(board[x][y].rect, (Vector2){board[x][y].rect.width/2, board[x][y].rect.height/2}, 0.0, temp_color);
        }

        if (!game_state) {
            DrawRectanglePro(start_button, (Vector2){0, 0}, 0.0, LIME);
            DrawText("Iniciar", start_button.x+10, start_button.y+5, start_button.height, WHITE);
            }
        else{
            DrawRectanglePro(start_button, (Vector2){0, 0}, 0.0, RED);
            DrawText("Parar", start_button.x+10, start_button.y+5, start_button.height, WHITE);
            }

        EndDrawing();
        ++current_frame;
    }

    clear_board_memory(board, rows);
    CloseWindow();
}
