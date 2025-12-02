#include "tipos.h"


void cria_tabuleiro(Tabuleiro *t, int lins, int cols) {
    t->lins = lins;
    t->cols = cols;
    
    
    t->grade = (Celula *)malloc(lins * cols * sizeof(Celula));
    
    if (t->grade == NULL) {
        printf("Erro: Sem memoria para criar tabuleiro.\n");
        exit(1);
    }

   
    for (int i = 0; i < lins * cols; i++) {
        t->grade[i].estado = AGUA;
        t->grade[i].id_navio = -1;
    }
}


void destroi_tabuleiro(Tabuleiro *t) {
    if (t->grade != NULL) {
        free(t->grade);
        t->grade = NULL;
    }
}


Celula* get_celula(Tabuleiro *t, int l, int c) {
    if (l < 0 || l >= t->lins || c < 0 || c >= t->cols) {
        return NULL;
    }
    
    return &t->grade[l * t->cols + c];
}


void mostra_tabuleiro(Tabuleiro *t, char *titulo, bool ver_navios) {
    printf("\n--- %s ---\n", titulo);
    printf("   ");
    for (int j = 0; j < t->cols; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < t->lins; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < t->cols; j++) {
            Celula *cel = get_celula(t, i, j);
            char simbolo = '~'; 

            if (cel->estado == ERROU) simbolo = '.';
            else if (cel->estado == ACERTOU) simbolo = 'X';
            else if (ver_navios && cel->estado == NAVIO) simbolo = 'S';
            
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}