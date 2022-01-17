#include "comum.h"

#if !defined(GAME_H)
#define GAME_H

celula** criar_tabuleiro();
int** criar_tabuleiro_auxiliar();
int checar_vizinhos(celula** tabuleiro, int x, int y);
int passo_jogo(celula** tabuleiro, int** aux_tabuleiro);
int resetar_tabuleiro(celula** tabuleiro);
int resetar_tabuleiro_auxiliar(int** tabuleiro);
int checar_clique(celula** tabuleiro, bool game_estado);
int limpar_memoria_tabuleiro(celula** tabuleiro);
int limpar_memoria_tabuleiro_auxiliar(int** tabuleiro);

#endif // GAME_H