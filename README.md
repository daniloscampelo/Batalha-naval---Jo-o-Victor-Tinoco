⚔️ Projeto Batalha Naval (PIF)

Gerenciamento Avançado de Memória em Linguagem C

Este projeto consiste na implementação completa do clássico jogo de estratégia Batalha Naval, desenvolvido rigorosamente em Linguagem C. O sistema opera via Linha de Comando (CLI) e foi concebido como um trabalho prático para demonstrar o domínio de conceitos avançados de programação estruturada e gestão de memória.

🎯 Objetivo Principal

O foco deste projeto é a aplicação prática e integrada de:

Alocação Dinâmica de Memória (malloc, free): Para criar os tabuleiros e vetores de navios em tempo de execução.

Manipulação de Ponteiros e Structs: Uso de estruturas aninhadas e aritmética de ponteiros para o acesso eficiente aos dados do tabuleiro linearizado.

Modularização: Divisão do código em arquivos com responsabilidades específicas.

✨ Funcionalidades

Menu Interativo: Navegação simples para iniciar partidas, configurar o tamanho do tabuleiro e sair.

Tabuleiro Dinâmico: O tamanho do campo de batalha pode ser configurado entre $6 \times 6$ e $26 \times 26$.

Posicionamento Automático: A frota é posicionada de forma inteligente e aleatória, garantindo que os navios não colidam e respeitem os limites do tabuleiro.

Ciclo de Jogo Completo: Alternância de turnos, processamento de tiro (Água, Acerto, Afundou) e detecção de vitória.

🏗️ Análise Técnica por Componente

A arquitetura do projeto é dividida em módulos que se comunicam através de funções e ponteiros, garantindo o princípio da Separação de Responsabilidades.

1. tipos.h (Definições de Estruturas)

Este arquivo de cabeçalho define as entidades do jogo:

Estrutura

Propósito

Detalhe Técnico

struct Tabuleiro

Representa o campo de batalha.

Contém Celula *grade, o ponteiro para o bloco de memória alocado dinamicamente.

struct Navio

Define as propriedades de cada embarcação.

Armazena tam (tamanho) e vidas (contador de acertos).

struct Jogador

Agrupa os recursos de um participante.

Contém duas instâncias de Tabuleiro (meu_jogo e meus_tiros) e a Frota, mostrando estruturas aninhadas.

enum EstadoCel

Define os estados visuais.

Tipos: AGUA, NAVIO, ACERTOU, ERROU.

2. tabuleiro.c (Gestão de Memória e Acesso)

Este módulo é o coração da manipulação de memória 2D em 1D:

void cria_tabuleiro(Tabuleiro *t, ...): Utiliza malloc(lins * cols * sizeof(Celula)) para alocar o vetor linear.

Celula* get_celula(Tabuleiro *t, int l, int c): A função mais crítica. Ela recebe coordenadas $2\text{D}$ (l, c) e retorna o ponteiro para a posição correta na memória linear. Isso é feito com a aritmética de ponteiros: &t->grade[l * t->cols + c].

void destroi_tabuleiro(Tabuleiro *t): Garante que free(t->grade) seja chamado, prevenindo vazamento de memória.

3. navios.c (Lógica da Frota)

Responsável por definir, alocar e posicionar as embarcações.

void monta_frota(Frota *f): Aloca o vetor de structs Navio (Frota.vetor_navios) e popula com os tamanhos padrão (5, 4, 3, 3, 2, 2).

posiciona_frota_auto(...): Implementa a lógica de tentativa e erro para posicionar navios. Utiliza a função cabe_aqui (que usa get_celula) para validar limites e colisões, garantindo que o posicionamento seja seguro.

4. main.c (Fluxo e Interação)

Contém o fluxo principal do jogo e a função de tiro.

int atirar(Jogador *atirador, Jogador *alvo, ...): Recebe ponteiros para os dois jogadores e as coordenadas. Atualiza o estado da Celula no tabuleiro do alvo e no mapa de tiros do atirador, demonstrando a passagem por referência para modificar estados globais.

main(): Gerencia o loop do menu, a configuração de tamanho, e inicia o ciclo jogar, chamando destroi_jogador no final para a limpeza de memória.

🛠️ Como Compilar e Rodar

O projeto utiliza um Makefile para automatizar a compilação de todos os módulos (main.c, tabuleiro.c, navios.c) e o link (ligação) para o executável final.

Pré-requisitos

É necessário ter o compilador GCC instalado e configurado no seu sistema.

Passo a Passo

Clone o Repositório:

git clone https://github.com/daniloscampelo/Batalha-naval---Jo-o-Victor-Tinoco
cd NomeDaPasta


Compile e Execute o Jogo:
Use o comando make run para compilar todos os arquivos e executar o jogo em seguida.

make run


Limpar Arquivos:
Para remover os arquivos objeto (.o) e o executável final:

make clean


Desenvolvido por: Danilo Santos Campelo | Disciplina: PIF - Sistemas de Informação
