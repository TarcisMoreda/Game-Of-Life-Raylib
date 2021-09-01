#include "../include/game.h"
#include <stdlib.h>

//definindo o que e uma celula
enum{vivo = 1, morto = 0};
struct celula{
    Rectangle rect;
    int estado;
};

//Funcao aloca memoria para o tabuleiro e preenche os dados de acordo
celula** criar_tabuleiro(int linhas, int colunas, int largura, int altura, int tamanho_celula){
    celula** tabuleiro = NULL;
    tabuleiro = (celula**) malloc(sizeof(celula*)*colunas);
    for (int x=0; x<colunas; x++) tabuleiro[x] = (celula*) malloc(sizeof(celula)*linhas);

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++){
        tabuleiro[x][y].rect.x = tamanho_celula*x;
        tabuleiro[x][y].rect.y = tamanho_celula*y;
        tabuleiro[x][y].rect.width = tamanho_celula;
        tabuleiro[x][y].rect.height = tamanho_celula;
        tabuleiro[x][y].estado = morto;
    }

    return tabuleiro;
}

//Funcao aloca memoria para o tabuleiro auxiliar e preenche os dados
int** criar_tabuleiro_auxiliar(int linhas, int colunas, int largura, int altura, int tamanho_celula){
    int** tabuleiro = NULL;
    tabuleiro = (int**) malloc(sizeof(int*)*colunas);
    for (int x=0; x<colunas; x++) tabuleiro[x] = (int*) malloc(sizeof(int)*linhas);

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y] = morto;

    return tabuleiro;
}

//Procura por todos os vizinhos da celula atual
int checar_vizinhos(celula** tabuleiro, int linhas, int colunas, int x, int y){
    int neighbours = 0;
    
    for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
            if (i == 0 && j == 0) continue;
            if (x+i == -1 || y+j == -1) continue;
            if (x+i == colunas || y+j == linhas) continue;
            if (tabuleiro[x+i][y+j].estado == vivo) neighbours++;
        }
    }

    return neighbours;
}

//Faz a proxima geracao do jogo
int passo_jogo(celula** tabuleiro, int** aux_tabuleiro, int linhas, int colunas, int largura, int altura, int tamanho_celula){
    if (tabuleiro == NULL) return 0;

    int neighbours;
    int temp;
    
    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    aux_tabuleiro[x][y] = tabuleiro[x][y].estado;
    
    
    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++){
        neighbours = checar_vizinhos(tabuleiro, linhas, colunas, x, y);
        
        if (tabuleiro[x][y].estado == vivo && (neighbours < 2 ||  neighbours > 3)) aux_tabuleiro[x][y] = morto;
        if (tabuleiro[x][y].estado == morto && neighbours == 3) aux_tabuleiro[x][y] = vivo;
    }
    
    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y].estado = aux_tabuleiro[x][y];

    resetar_tabuleiro_auxiliar(aux_tabuleiro, linhas, colunas);

    return 1;
}

//Desenha o tabuleiro na tela
int mostrar_tabuleiro(celula** tabuleiro, int linhas, int colunas, int largura, int tamanho_celula){
    if (tabuleiro == NULL) return 0;

    Color cor_temp;

    for (int x=0; x<colunas; x++){
        for (int y=0; y<linhas; y++){
            if (tabuleiro[x][y].estado == vivo) cor_temp = BLACK;
            else if (tabuleiro[x][y].estado == morto) cor_temp = WHITE;
            DrawRectangleRec(tabuleiro[x][y].rect, cor_temp);
            DrawLine(0, y*tamanho_celula, largura, y*tamanho_celula, BLACK);
        }
        DrawLine(x*tamanho_celula, 0, x*tamanho_celula, linhas*tamanho_celula, GRAY);
    }

    return 1;
}

//Reseta o estado de todas as celulas para morta
int resetar_tabuleiro(celula** tabuleiro, int linhas, int colunas){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y].estado = morto;

    return 1;
}

//Reseta o estado de todas as celulas do auxiliar para morta
int resetar_tabuleiro_auxiliar(int** tabuleiro, int linhas, int colunas){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y] = morto;

    return 1;
}

//Checa por click em celula do tabuleiro e muda seu estado
int checar_clique(celula** tabuleiro, int linhas, int colunas, bool game_estado){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++) 
    for (int y=0; y<linhas; y++)
    if (CheckCollisionPointRec(GetMousePosition(), tabuleiro[x][y].rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !game_estado)
    tabuleiro[x][y].estado = !tabuleiro[x][y].estado;

    return 1;
}

//Limpa a memoria do tabuleiro
int limpar_memoria_tabuleiro(celula** tabuleiro, int colunas){
    if (tabuleiro == NULL) return 0;
    
    for (int x=0; x<colunas; x++) free(tabuleiro[x]);
    free(tabuleiro);

    return 1;
}

//Limpa a memoria do auxiliar
int limpar_memoria_tabuleiro_auxiliar(int** tabuleiro, int colunas){
    if (tabuleiro == NULL) return 0;
    
    for (int x=0; x<colunas; x++) free(tabuleiro[x]);
    free(tabuleiro);

    return 1;
}