Relatório Técnico: Batalha Naval - Programação Imperativa e Funcional

1. Introdução e Objetivos

Este documento descreve a arquitetura, as decisões de design e a implementação do projeto Batalha Naval, desenvolvido para a disciplina de Programação Imperativa e Funcional (PIF) da Cesar.

O objetivo principal foi demonstrar o domínio de conceitos essenciais da Linguagem C, com foco especial em:

Alocação e Gerenciamento Dinâmico de Memória (malloc, free).

Manipulação Avançada de Ponteiros.

Modelagem de Dados utilizando Estruturas (structs) e enums.

Arquitetura modular e organizada.

2. Arquitetura do Projeto e Modularização

O sistema foi dividido em módulos coesos para garantir a Separação de Responsabilidades, conforme exigido.

Módulo

Arquivos

Responsabilidade

Definições

tipos.h

Contém todas as declarações de structs (Tabuleiro, Navio, Jogador) e enums (EstadoCel, Orientacao).

Tabuleiros

tabuleiro.c

Gerencia a memória (cria_tabuleiro, destroi_tabuleiro) e o acesso 2D na matriz linearizada (get_celula).

Frota

navios.c

Lógica de montagem da frota, posicionamento automático (posiciona_frota_auto) e validação de colocação.

Principal

main.c

Contém o Core Loop do jogo, Menu, lógica de turno (jogar), validação de entrada e detecção de vitória.

(Inclua aqui um breve diagrama do fluxo de chamadas entre main.c e os outros módulos.)

3. Estruturas de Dados e Gestão de Memória

A base do projeto é o uso consciente e eficiente da memória, evitando alocações estáticas e garantindo o controle total sobre o espaço de endereço.

3.1. Tabuleiro e Aritmética de Ponteiros

O Tabuleiro é representado como uma estrutura com um único ponteiro: Celula *grade.

Alocação: Utilizamos malloc(lins * cols * sizeof(Celula)) para alocar o tabuleiro como um vetor unidimensional linearizado.

Acesso: A função get_celula(Tabuleiro *t, int l, int c) é crucial. Ela traduz as coordenadas 2D (linha, coluna) para o índice correto no vetor 1D, usando a fórmula:


$$\text{Endereço} = \&(\text{t}\rightarrow\text{grade}[\text{l} \times \text{t}\rightarrow\text{cols} + \text{c}])$$

Desalocação: A função destroi_tabuleiro garante que free(t->grade) seja chamado, prevenindo Memory Leaks.

3.2. Estruturas e Ponteiros

struct Jogador: Contém as duas estruturas Tabuleiro (meu_jogo e meus_tiros) e a Frota, mostrando o uso de estruturas aninhadas.

Passagem por Referência: Todas as funções críticas (atirar, configura_jogador) recebem ponteiros (Jogador *p ou Tabuleiro *t) para modificar o estado global do jogo diretamente, otimizando a performance.

4. Fluxo de Execução e Regras do Jogo

O programa inicia em main.c com um loop de menu que permite Novo Jogo, Configurações ou Sair.

Inicialização: O main chama configura_jogador para ambos os participantes, que por sua vez chama cria_tabuleiro (alocação) e posiciona_frota_auto (posicionamento).

Loop Principal (jogar): O jogo alterna entre o Jogador *atual e o Jogador *inimigo.

Tiro e Validação: O sistema garante que a coordenada de tiro seja válida (dentro dos limites e não repetida) antes de chamar atirar.

Processamento de Resultado: A função atirar atualiza dois tabuleiros (meus_tiros do atirador e meu_jogo do alvo) e a contagem de vidas do Navio atingido.

Vitória: A condição de vitória é checada a cada tiro, verificando se inimigo->frota.vivos == 0.

5. Decisões de Design

Validação Rigorosa: Implementamos laços while e verificações no main.c para garantir que as entradas do usuário (tamanho do tabuleiro, coordenadas) respeitem os limites e o formato esperado.

Encapsulamento de Acesso: A lógica de acesso ao vetor 1D foi encapsulada na função get_celula (tabuleiro.c). Isso permite que os outros módulos manipulem o tabuleiro como se fosse 2D, sem se preocupar com a aritmética de ponteiros interna.

6. Conclusão

Este projeto demonstrou a capacidade do time de planejar, construir e depurar um sistema complexo em C, priorizando a eficiência de memória e a clareza arquitetural. O domínio de ponteiros e alocação dinâmica foi integral para o sucesso da implementação, atendendo aos requisitos da disciplina PIF.
