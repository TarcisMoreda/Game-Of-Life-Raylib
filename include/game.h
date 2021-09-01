#include <raylib.h>
#include <stdio.h>

typedef struct celula celula;

celula** criar_tabuleiro(int linhas, int colunas, int tamanho_celula);
int** criar_tabuleiro_auxiliar(int linhas, int colunas, int tamanho_celula);
int checar_vizinhos(celula** tabuleiro, int linhas, int colunas, int x, int y);
int passo_jogo(celula** tabuleiro, int** aux_tabuleiro, int linhas, int colunas, int tamanho_celula);
int mostrar_tabuleiro(celula** tabuleiro, int linhas, int colunas, int tamanho_celula);
int resetar_tabuleiro(celula** tabuleiro, int linhas, int colunas);
int resetar_tabuleiro_auxiliar(int** tabuleiro, int linhas, int colunas);
int checar_clique(celula** tabuleiro, int linhas, int colunas, bool game_estado);
int limpar_memoria_tabuleiro(celula** tabuleiro, int colunas);
int limpar_memoria_tabuleiro_auxiliar(int** tabuleiro, int colunas);