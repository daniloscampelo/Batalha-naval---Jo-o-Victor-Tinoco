#include "tipos.h"


Celula* get_celula(Tabuleiro *t, int l, int c);

void monta_frota(Frota *f) {
    f->qtd_total = 6;
    f->vetor_navios = (Navio *)malloc(f->qtd_total * sizeof(Navio));
    f->vivos = f->qtd_total;

    
    strcpy(f->vetor_navios[0].nome, "Porta-Avioes"); f->vetor_navios[0].tam = 5;
    strcpy(f->vetor_navios[1].nome, "Encouracado"); f->vetor_navios[1].tam = 4;
    strcpy(f->vetor_navios[2].nome, "Cruzador A"); f->vetor_navios[2].tam = 3;
    strcpy(f->vetor_navios[3].nome, "Cruzador B"); f->vetor_navios[3].tam = 3;
    strcpy(f->vetor_navios[4].nome, "Destroyer A"); f->vetor_navios[4].tam = 2;
    strcpy(f->vetor_navios[5].nome, "Destroyer B"); f->vetor_navios[5].tam = 2;

    for (int i = 0; i < f->qtd_total; i++) {
        f->vetor_navios[i].vidas = 0;
        f->vetor_navios[i].afundado = false;
    }
}


bool cabe_aqui(Tabuleiro *t, int l, int c, int tam, Orientacao o) {
    for (int i = 0; i < tam; i++) {
        int nl = l + (o == VERTICAL ? i : 0);
        int nc = c + (o == HORIZONTAL ? i : 0);

        Celula *cel = get_celula(t, nl, nc);
        
        if (cel == NULL || cel->estado != AGUA) {
            return false; 
        }
    }
    return true;
}


void posiciona_frota_auto(Tabuleiro *t, Frota *f) {
    for (int i = 0; i < f->qtd_total; i++) {
        bool posicionado = false;
        while (!posicionado) {
            int l = rand() % t->lins;
            int c = rand() % t->cols;
            Orientacao o = rand() % 2;

            if (cabe_aqui(t, l, c, f->vetor_navios[i].tam, o)) {
                f->vetor_navios[i].lin_inicio = l;
                f->vetor_navios[i].col_inicio = c;
                f->vetor_navios[i].orientacao = o;

                for (int k = 0; k < f->vetor_navios[i].tam; k++) {
                    int nl = l + (o == VERTICAL ? k : 0);
                    int nc = c + (o == HORIZONTAL ? k : 0);
                    
                    Celula *cel = get_celula(t, nl, nc);
                    cel->estado = NAVIO;
                    cel->id_navio = i;
                }
                posicionado = true;
            }
        }
    }
}

void libera_frota(Frota *f) {
    if (f->vetor_navios != NULL) {
        free(f->vetor_navios);
        f->vetor_navios = NULL;
    }
}