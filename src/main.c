#include "../include/game.h"

int main(int argc, char const *argv[]){
    //Alocando toda a memoria nescessaria para o jogo funcionar
    celula** tabuleiro = criar_tabuleiro(linhas, colunas, tamanho_celula);
    int** tabuleiro_auxiliar = criar_tabuleiro_auxiliar(linhas, colunas, tamanho_celula);

    //Variaveis para a logica do jogo
    bool estado_jogo = false;
    int frame_atual = 0;
    char str_geracao[50];
    int geracao = 0;

    //Criando os botoes
    Rectangle botao_iniciar;
    botao_iniciar.x = 0;
    botao_iniciar.y = linhas*tamanho_celula;
    botao_iniciar.width = 200;
    botao_iniciar.height = altura_janela;
    Rectangle botao_limpar;
    botao_limpar.x = largura_janela-200;
    botao_limpar.y = linhas*tamanho_celula;
    botao_limpar.width = 200;
    botao_limpar.height = altura_janela;

    //Iniciando a janela e configurando
    InitWindow(largura_janela, altura_janela, "Conway's Game of Life");
    SetTargetFPS(fps);

    //Loop principal do jogo
    while (!WindowShouldClose()){
        //Logica do clique no taabuleiro
        checar_clique(tabuleiro, estado_jogo);

        //Logica dos botoes
        if (CheckCollisionPointRec(GetMousePosition(), botao_iniciar) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) estado_jogo = !estado_jogo;
        if (CheckCollisionPointRec(GetMousePosition(), botao_limpar) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !estado_jogo){
            resetar_tabuleiro(tabuleiro);
            geracao = 0;
        }

        //Condicao para a proxima geracao
        if (frame_atual%frames_por_geracao == 0 && estado_jogo){
            passo_jogo(tabuleiro, tabuleiro_auxiliar);
            ++geracao;
        }

        //Concatenando str das geracoes
        snprintf(str_geracao, 50, "Geracao: %d", geracao);

        BeginDrawing();
        ClearBackground(GRAY);

        mostrar_tabuleiro(tabuleiro);

        //Logica para a mudanca de cor e texto do botao botao_iniciar
        if (!estado_jogo) {
            DrawRectangleRec(botao_iniciar, LIME);
            DrawText("Iniciar", botao_iniciar.x+10, botao_iniciar.y+5, altura_janela-botao_iniciar.y, WHITE);
            }
        else{
            DrawRectangleRec(botao_iniciar, RED);
            DrawText("Parar", botao_iniciar.x+10, botao_iniciar.y+5, altura_janela-botao_iniciar.y, WHITE);
            }

        DrawRectangleRec(botao_limpar, BROWN);
        DrawText("Limpar", botao_limpar.x+20, botao_limpar.y+5, altura_janela-botao_limpar.y, WHITE);

        DrawText(str_geracao, botao_iniciar.width+10, botao_iniciar.y+5, altura_janela-botao_limpar.y, WHITE);

        EndDrawing();
        if (estado_jogo) ++frame_atual;
    }

    //Limpando memoria e finalizando raylib
    limpar_memoria_tabuleiro(tabuleiro);
    limpar_memoria_tabuleiro_auxiliar(tabuleiro_auxiliar);
    CloseWindow();

    return 0;
}