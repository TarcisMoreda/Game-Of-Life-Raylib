#include "../include/renderizador.h"

//Desenha o tabuleiro na tela
int mostrar_tabuleiro(celula** tabuleiro){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++){
        for (int y=0; y<linhas; y++){
            if (tabuleiro[x][y].estado == vivo) 
            DrawRectangleRec(tabuleiro[x][y].rect, BLACK);
            else DrawRectangleRec(tabuleiro[x][y].rect, WHITE);

            DrawLine(0, y*tamanho_celula, colunas*tamanho_celula, y*tamanho_celula, BLACK);
        }
        DrawLine(x*tamanho_celula, 0, x*tamanho_celula, linhas*tamanho_celula, BLACK);
    }

    return 1;
}