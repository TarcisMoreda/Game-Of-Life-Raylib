#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#if !defined(COMUM_H)
#define COMUM_H

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

typedef struct celula{
    Rectangle rect;
    int estado;
} celula;

#endif // COMUM_H