#include "tipos.h"


void cria_tabuleiro(Tabuleiro *t, int lins, int cols);
void destroi_tabuleiro(Tabuleiro *t);
Celula* get_celula(Tabuleiro *t, int l, int c);
void mostra_tabuleiro(Tabuleiro *t, char *titulo, bool ver_navios);
void monta_frota(Frota *f);
void posiciona_frota_auto(Tabuleiro *t, Frota *f);
void libera_frota(Frota *f);

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int atirar(Jogador *atirador, Jogador *alvo, int l, int c) {
    Celula *cel_alvo = get_celula(&alvo->meu_jogo, l, c);
    Celula *cel_tiro = get_celula(&atirador->meus_tiros, l, c);

    if (cel_alvo == NULL) return -1;
    if (cel_tiro->estado != AGUA) return -1; 

    if (cel_alvo->estado == NAVIO) {
        cel_alvo->estado = ACERTOU;
        cel_tiro->estado = ACERTOU;
        
        int id = cel_alvo->id_navio;
        Navio *n = &alvo->frota.vetor_navios[id];
        n->vidas++;

        printf("\n>>> FOGO! Acertou o %s!\n", n->nome);

        if (n->vidas >= n->tam) {
            n->afundado = true;
            alvo->frota.vivos--;
            printf(">>> KABUM! O %s foi afundado!\n", n->nome);
            return 2;
        }
        return 1;
    } else {
        cel_tiro->estado = ERROU;
        printf("\n>>> Agua...\n");
        return 0;
    }
}

void configura_jogador(Jogador *p, char *nome, int l, int c) {
    strcpy(p->apelido, nome);
    cria_tabuleiro(&p->meu_jogo, l, c);
    cria_tabuleiro(&p->meus_tiros, l, c);
    monta_frota(&p->frota);
    posiciona_frota_auto(&p->meu_jogo, &p->frota); 
}

void destroi_jogador(Jogador *p) {
    destroi_tabuleiro(&p->meu_jogo);
    destroi_tabuleiro(&p->meus_tiros);
    libera_frota(&p->frota);
}

void jogar(int tamanhoDoTabuleiro, int posicionamento) {
    Jogador p1, p2;
    int linhas = tamanhoDoTabuleiro, colunas = tamanhoDoTabuleiro;
    int vez = 1; 
    bool fim_jogo = false;
    char nomeJogador1[100], nomeJogador2[100];

    printf("=== BATALHA NAVAL ===\n");
    
    printf("Informe o apelido do Jogador 1: ");
    scanf("%s", nomeJogador1);
    printf("\n");
    
    printf("Informe o apelido do Jogador 2: ");
    scanf("%s", nomeJogador2);
    printf("\n");
    
    configura_jogador(&p1, nomeJogador1, linhas, colunas);
    configura_jogador(&p2, nomeJogador2, linhas, colunas);
    
    while (!fim_jogo) {
        Jogador *atual = (vez == 1) ? &p1 : &p2;
        Jogador *inimigo = (vez == 1) ? &p2 : &p1;

        printf("\n========================================\n");
        printf("VEZ DE: %s\n", atual->apelido);
        
        mostra_tabuleiro(&atual->meus_tiros, "SEUS TIROS", false);
        

        char entrada[10];
        int l = -1, c = -1;
        bool entrada_ok = false;

        while (!entrada_ok) {
            printf("Coordenada (ex: A5): ");
            if (scanf("%s", entrada) != 1) break;
            
            c = toupper(entrada[0]) - 'A';
            l = atoi(&entrada[1]) - 1;

            Celula *teste = get_celula(&atual->meus_tiros, l, c);
            if (teste == NULL) {
                printf("Invalido. Tente A-%c e 1-%d.\n", 'A'+colunas-1, linhas);
            } else if (teste->estado != AGUA) {
                printf("Ja atirou ai.\n");
            } else {
                entrada_ok = true;
            }
        }

        atirar(atual, inimigo, l, c);

        if (inimigo->frota.vivos == 0) {
            printf("\n\n################################\n");
            printf("VITORIA DE %s!\n", atual->apelido);
            printf("################################\n");
            fim_jogo = true;
        } else {
            printf("Pressione ENTER para passar a vez...");
            limpa_buffer(); 
            getchar();
            vez = (vez == 1) ? 2 : 1;
        }
    }

    destroi_jogador(&p1);
    destroi_jogador(&p2);
}

void configuracoes(int *tamanhoDoTabuleiro, int *posicionamento){
    char caractere;
    printf("Tamanho do tabuleiro (6-26): \n");
    scanf("%d", tamanhoDoTabuleiro);
    
    while(*tamanhoDoTabuleiro < 6 || *tamanhoDoTabuleiro >26) {
        printf("Tamanho inválido!, escolha de 6-26\n");
        scanf("%d", tamanhoDoTabuleiro);
    }
    
    printf("Posicionamento (M)anual ou (A)utomático?\n");
    scanf(" %c", &caractere);
    
    while(caractere != 'M' && caractere != 'A') {
        printf("Opção inválida, coloque (M) ou (A)\n");
        scanf(" %c", &caractere);
    }
    
    if(caractere == 'A') *posicionamento = 0;
    if(caractere == 'M') *posicionamento = 1;
    
    
}

int main() {
    srand(time(NULL));
    int tamanhoDoTabuleiro = 10;
    int posicionamento = 0; // 0: Automatica e 1: Manual
    
    int opcao;
    while(true) {
        printf("=== BATALHA NAVAL ===\n");
        printf("1) Novo jogo\n");
        printf("2) Configurações\n");
        printf("3) Sair\n");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                jogar(tamanhoDoTabuleiro, posicionamento);
                break;
            case 2:
                configuracoes(&tamanhoDoTabuleiro, &posicionamento);
                break;
            case 3:
                // sair();
                return 0;
            default:
                printf("Opção inválida! Digite novamente\n");
                break;
        }
            
    }
    

    return 0;
}