#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

//Definindo constantes que podem ser alteradas para uma experiencia diferente
#define largura_janela 800
#define altura_janela 600
#define tamanho_celula 8
#define colunas (int) (largura_janela/tamanho_celula)
#define linhas (int) ((altura_janela-50)/tamanho_celula)
#define fps 60
#define geracoes_por_segundo 5
#define frames_por_geracao (int) (fps/geracoes_por_segundo)

//definindo os estados de uma celula
enum{vivo = 1, morto = 0};

typedef struct{
    Rectangle rect;
    int estado;
} celula;

celula** criar_tabuleiro();
int** criar_tabuleiro_auxiliar();
int checar_vizinhos(celula** tabuleiro, int x, int y);
int passo_jogo(celula** tabuleiro, int** aux_tabuleiro);
int mostrar_tabuleiro(celula** tabuleiro);
int resetar_tabuleiro(celula** tabuleiro);
int resetar_tabuleiro_auxiliar(int** tabuleiro);
int checar_clique(celula** tabuleiro, bool game_estado);
int limpar_memoria_tabuleiro(celula** tabuleiro);
int limpar_memoria_tabuleiro_auxiliar(int** tabuleiro);