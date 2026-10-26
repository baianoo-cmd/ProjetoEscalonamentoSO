#include <stdio.h>
#include <stdlib.h>
#include "priority.h"


int escolherProcesso(struct Processo processos[], int n, int concluidos[], int tempo) {
    int escolhido = -1;

    for (int i = 0; i < n; i++) {
        if (concluidos[i] == 0 &&
            processos[i].chegada <= tempo) {

            if (escolhido == -1 || processos[i].prioridade < processos[escolhido].prioridade || (processos[i].prioridade == processos[escolhido].prioridade && processos[i].chegada < processos[escolhido].chegada)) {

                escolhido = i;
            }
        }
    }

    return escolhido;
}


void escalonarPriority(struct Processo processos[], int n) {
    int concluidos[n];
    int tempo = 0;
    int quantidadeConcluidos = 0;

    for (int i = 0; i < n; i++) {
        concluidos[i] = 0;
    }

    while (quantidadeConcluidos < n) {
        int escolhido = escolherProcesso(processos, n, concluidos, tempo);

        if (escolhido == -1) {
            tempo++;
            continue;
        }

        int inicio = tempo;
        int termino = inicio + processos[escolhido].burst;

        printf("Processo P%d: inicio = %d, termino = %d\n", processos[escolhido].id, inicio, termino);

        tempo = termino;
        concluidos[escolhido] = 1;
        quantidadeConcluidos++;
    }
}

int main(void){
    int n;

    printf("Quantidade de processos: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalide. \n");
        return 1;
    }

    struct Processo processos[n];

    for(int i = 0; i < n; i++) {
        processos[i].id = i + 1;
        printf("\nProcesso P%d\n", processos[i].id);


        printf("Tempo de chegada: ");
        if (scanf("%d", &processos[i].chegada) != 1 || processos[i].chegada < 0) {
            printf("Tempo de chegada invalido.\n");
            return 1;
        }

        printf("Tempo de execução (burst): ");
        if (scanf ("%d", &processos[i].burst) != 1 || processos[i].burst <= 0) {
            printf("Tempo de execução invalido.\n");
            return 1;
        }

        printf("Prioridade (numero menor = prioridade maior): ");
        if (scanf("%d", &processos[i].prioridade) != 1) {
            printf("Prioridade invalida.\n");
            return 1;
        }
    }

    printf("\n - ESCALONAMENTO POR PRIORIDADE - \n");
    escalonarPriority(processos, n);

    return 0;
}

