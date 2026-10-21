#ifndef PRIORITY_H
#define PRIORITY_H

struct Processo
    {
    int id;
    int chegada;
    int burst;
    int prioridade;
};

int escolherProcesso(struct Processo processos[], int n, int concluidos[], int tempo);

void escalonarPriority(struct Processo processos[], int n);

#endif
