#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int tempoExecucao;
    int tempoEspera;
    int tat;
} Processo;

typedef struct {
    Processo elementos[100];
    int inicio;
    int fim;
    int tamanho;
} FilaProcessos;

void inicializarFila(FilaProcessos *f){
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

void enfileirar(FilaProcessos *f, Processo p){
    if(f->tamanho < 100){
        f->fim++;
        f->elementos[f->fim] = p;
        f->tamanho++;
    }
}

void organizarFilaSJF(FilaProcessos *f){
    Processo temp;
    for(int i = 0; i < f->tamanho - 1; i++){
        for(int j = i + 1; j < f->tamanho; j++){
            if(f->elementos[j].tempoExecucao< f->elementos[i].tempoExecucao){
                temp = f->elementos[i];
                f->elementos[i] = f->elementos[j];
                f->elementos[j] = temp;
            }
        }
    }
}

int main(){
    int n;

    printf("--- ESCALONADOR SJF COM ESTRUTURA DE FILA ---\n");
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    FilaProcessos fila;
    inicializarFila(&fila);

    for(int i = 0; i < n; i++){
        Processo p;
        p.id = i + 1;
        printf("Digite o tempo de execucao para o P%d: ", p.id);
        scanf("%d", &p.tempoExecucao);
        p.tempoEspera = 0;
        p.tat = 0;
        
        enfileirar(&fila, p);
    }

    organizarFilaSJF(&fila);

    float total_espera = 0, total_tat = 0;

    for(int i = 0; i < fila.tamanho; i++){
        if(i == 0){
            fila.elementos[i].tempoEspera = 0;
        }else{
            fila.elementos[i].tempoEspera = fila.elementos[i - 1].tempoEspera + fila.elementos[i - 1].tempoExecucao;
        }
        
        fila.elementos[i].tat = fila.elementos[i].tempoExecucao + fila.elementos[i].tempoEspera;

        total_espera += fila.elementos[i].tempoEspera;
        total_tat += fila.elementos[i].tat;
    }

    printf("---ORDEM DE EXECUCAO DOS PROCESSOS---\n");
    printf("=====================================\n");

    for(int i = 0; i < fila.tamanho; i++){
        printf("\nProcesso: P%d\n", fila.elementos[i].id);
        printf("Tempo de Execucao: %d\n", fila.elementos[i].tempoExecucao);
        printf("Tempo de Espera: %d\n", fila.elementos[i].tempoEspera);
        printf("Turnaround Time: %d\n", fila.elementos[i].tat);
        printf("-----------------------------------------\n");
    }

    printf("\n--- RESULTADOS GERAIS ---\n");
    printf("Media do Tempo de Espera = %.2f\n", total_espera / n);
    printf("Media do Turnaround Time = %.2f\n", total_tat / n);
    printf("=========================================\n");

    return 0;
}