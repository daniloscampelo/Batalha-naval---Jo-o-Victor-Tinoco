#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>


typedef enum { AGUA, NAVIO, ACERTOU, ERROU } EstadoCel;


typedef enum { HORIZONTAL, VERTICAL } Orientacao;


typedef struct {
    EstadoCel estado;
    int id_navio; 
} Celula;


typedef struct {
    int lins;
    int cols;
    Celula *grade; 
} Tabuleiro;


typedef struct {
    char nome[20];
    int tam;
    int vidas;    
    bool afundado;
    int lin_inicio;
    int col_inicio;
    Orientacao orientacao;
} Navio;


typedef struct {
    Navio *vetor_navios; 
    int qtd_total;
    int vivos;
} Frota;


typedef struct {
    char apelido[32];
    Tabuleiro meu_jogo;   
    Tabuleiro meus_tiros; 
    Frota frota;
    int total;
    int acertos;
} Jogador;

#endif