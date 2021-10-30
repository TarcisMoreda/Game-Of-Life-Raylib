#include "../include/game.h"

//Funcao aloca memoria para o tabuleiro e preenche os dados de acordo
celula** criar_tabuleiro(){
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
int** criar_tabuleiro_auxiliar(){
    int** tabuleiro = NULL;
    tabuleiro = (int**) malloc(sizeof(int*)*colunas);
    for (int x=0; x<colunas; x++) tabuleiro[x] = (int*) malloc(sizeof(int)*linhas);

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y] = morto;

    return tabuleiro;
}

//Procura por todos os vizinhos da celula atual
int checar_vizinhos(celula** tabuleiro, int x, int y){
    int vizinhos = 0;
    
    for (int i=-1; i<=1; i++)
    for (int j=-1; j<=1; j++){
        if (i == 0 && j == 0) continue;
        if (x+i == -1 || y+j == -1) continue;
        if (x+i == colunas || y+j == linhas) continue;
        if (tabuleiro[x+i][y+j].estado == vivo) ++vizinhos;
    }

    return vizinhos;
}

//Faz a proxima geracao do jogo
int passo_jogo(celula** tabuleiro, int** aux_tabuleiro){
    if (tabuleiro == NULL) return 0;

    int vizinhos;

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++){
        aux_tabuleiro[x][y] = tabuleiro[x][y].estado;
        vizinhos = checar_vizinhos(tabuleiro, x, y);
        
        if (tabuleiro[x][y].estado == vivo && (vizinhos < 2 ||  vizinhos > 3)) aux_tabuleiro[x][y] = morto;
        if (tabuleiro[x][y].estado == morto && vizinhos == 3) aux_tabuleiro[x][y] = vivo;
    }
    
    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y].estado = aux_tabuleiro[x][y];

    resetar_tabuleiro_auxiliar(aux_tabuleiro);

    return 1;
}

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

//Reseta o estado de todas as celulas para morta
int resetar_tabuleiro(celula** tabuleiro){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y].estado = morto;

    return 1;
}

//Reseta o estado de todas as celulas do auxiliar para morta
int resetar_tabuleiro_auxiliar(int** tabuleiro){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++)
    for (int y=0; y<linhas; y++)
    tabuleiro[x][y] = morto;

    return 1;
}

//Checa por click em celula do tabuleiro e muda seu estado
int checar_clique(celula** tabuleiro, bool game_estado){
    if (tabuleiro == NULL) return 0;

    for (int x=0; x<colunas; x++) 
    for (int y=0; y<linhas; y++){
    if (CheckCollisionPointRec(GetMousePosition(), tabuleiro[x][y].rect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !game_estado)
    tabuleiro[x][y].estado = vivo;
    else if (CheckCollisionPointRec(GetMousePosition(), tabuleiro[x][y].rect) && IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && !game_estado)
    tabuleiro[x][y].estado = morto;
    }

    return 1;
}

//Limpa a memoria do tabuleiro
int limpar_memoria_tabuleiro(celula** tabuleiro){
    if (tabuleiro == NULL) return 0;
    
    for (int x=0; x<colunas; x++) free(tabuleiro[x]);
    free(tabuleiro);

    return 1;
}

//Limpa a memoria do auxiliar
int limpar_memoria_tabuleiro_auxiliar(int** tabuleiro){
    if (tabuleiro == NULL) return 0;
    
    for (int x=0; x<colunas; x++) free(tabuleiro[x]);
    free(tabuleiro);

    return 1;
}