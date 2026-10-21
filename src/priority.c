#include <stdio.h>
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

