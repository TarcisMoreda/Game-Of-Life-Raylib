#include "../include/game.h"

int main(int argc, char const *argv[]){
    const int win_width = 800;
    const int win_height = 600;
    const int cell_size = 16;
    const int cols = (int) win_width/cell_size;
    const int rows = (int) ((win_height-(3*cell_size))/cell_size);
    const int fps = 60;
    const int generations_per_sec = 3;
    const int frames_per_generation = fps/generations_per_sec;

    cell** board = create_board(rows, cols, win_width, win_height, cell_size);
    Color temp_color;
    bool game_state = false;
    int current_frame = 0;

    InitWindow(win_width, win_height, "Conway's Game of Life");
    SetTargetFPS(fps);

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

    while (!WindowShouldClose()){
        click_state(board, rows, cols, game_state);

        if (CheckCollisionPointRec(GetMousePosition(), start_button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        game_state = !game_state;

        if (CheckCollisionPointRec(GetMousePosition(), clear_button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_state)
        reset_board(board, rows, cols);

        if (current_frame%frames_per_generation == 0 && game_state)
        game_step(board, rows, cols, win_width, win_height, cell_size);

        BeginDrawing();
        ClearBackground(GRAY);

        show_board(board, rows, cols, win_width, cell_size);

        if (!game_state) {
            DrawRectanglePro(start_button, (Vector2){0, 0}, 0.0, LIME);
            DrawText("Iniciar", start_button.x+10, start_button.y+5, win_height-(cell_size*rows), WHITE);
            }
        else{
            DrawRectanglePro(start_button, (Vector2){0, 0}, 0.0, RED);
            DrawText("Parar", start_button.x+10, start_button.y+5, win_height-(cell_size*rows), WHITE);
            }

        DrawRectanglePro(clear_button, (Vector2){0, 0}, 0.0, BROWN);
        DrawText("Limpar", clear_button.x+20, clear_button.y+5, win_height-(cell_size*rows), WHITE);

        EndDrawing();
        ++current_frame;
    }

    clear_board_memory(board, cols);
    CloseWindow();
}
