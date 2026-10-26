#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSOS 100
#define TAM_FILA (MAX_PROCESSOS + 1)

typedef struct {
    int id;
    int chegada;
    int burst;
    int restante;
    int conclusao;
    int retorno;
    int espera;
} Processo;

typedef struct {
    int dados[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

/* Inicializa a fila */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

/* Insere um processo no final da fila */
int enfileirar(Fila *f, int indice) {
    if (f->quantidade == TAM_FILA) {
        return 0;
    }

    f->dados[f->fim] = indice;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;

    return 1;
}

/* Retira o primeiro processo da fila */
int desenfileirar(Fila *f) {
    int indice;

    if (f->quantidade == 0) {
        return -1;
    }

    indice = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return indice;
}

/* Le um numero inteiro e rejeita entradas invalidas */
int lerInteiro(const char *mensagem, int minimo, int maximo) {
    int valor;
    int resultado;
    int caractere;

    while (1) {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);

        if (resultado == 1) {
            do {
                caractere = getchar();
            } while (caractere != '\n' &&
                     caractere != EOF);

            if (valor >= minimo && valor <= maximo) {
                return valor;
            }
        } else {
            if (resultado == EOF) {
                exit(EXIT_FAILURE);
            }

            do {
                caractere = getchar();
            } while (caractere != '\n' &&
                     caractere != EOF);
        }

        printf("Entrada invalida. Tente novamente.\n");
    }
}

/* Ordena os processos por chegada, preservando a ordem
   de identificacao quando os tempos de chegada empatam. */
void ordenarPorChegada(Processo p[], int n) {
    int i, j;
    Processo temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].chegada > p[j].chegada ||
                (p[i].chegada == p[j].chegada &&
                 p[i].id > p[j].id)) {

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

/* Reorganiza os processos pelo identificador original */
void ordenarPorId(Processo p[], int n) {
    int i, j;
    Processo temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].id > p[j].id) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main(void) {
    Processo p[MAX_PROCESSOS];
    Fila fila;

    int n, quantum;
    int i;
    int proximo = 0;
    int tempo = 0;
    int concluidos = 0;
    int indice;
    int executado;
    int inicioExecucao;

    double somaEspera = 0.0;
    double somaRetorno = 0.0;

    printf("=== Escalonamento Round Robin ===\n\n");

    n = lerInteiro(
        "Quantidade de processos (1 a 100): ",
        1, MAX_PROCESSOS
    );

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\n--- Processo P%d ---\n", p[i].id);

        p[i].chegada = lerInteiro(
            "Tempo de chegada (>= 0): ",
            0, 1000000
        );

        p[i].burst = lerInteiro(
            "Tempo de execucao (>= 1): ",
            1, 1000000
        );

        p[i].restante = p[i].burst;
        p[i].conclusao = 0;
        p[i].retorno = 0;
        p[i].espera = 0;
    }

    quantum = lerInteiro(
        "\nInforme o quantum (>= 1): ",
        1, 1000000
    );

    /* Ordena para controlar corretamente as chegadas */
    ordenarPorChegada(p, n);

    inicializarFila(&fila);

    printf("\n=== ORDEM DE EXECUCAO ===\n");

    while (concluidos < n) {

        /* Se nao ha processos prontos, avanca o relogio
           ate a chegada do proximo processo. */
        if (fila.quantidade == 0 && proximo < n) {
            if (tempo < p[proximo].chegada) {
                tempo = p[proximo].chegada;
            }
        }

        /* Insere na fila todos os processos que ja chegaram */
        while (proximo < n &&
               p[proximo].chegada <= tempo) {

            if (!enfileirar(&fila, proximo)) {
                printf("Erro ao inserir processo na fila.\n");
                return EXIT_FAILURE;
            }

            proximo++;
        }

        /* Retira o primeiro processo da fila */
        indice = desenfileirar(&fila);

        if (indice == -1) {
            continue;
        }

        inicioExecucao = tempo;

        /* O processo usa a CPU por ate um quantum */
        if (p[indice].restante > quantum) {
            executado = quantum;
        } else {
            executado = p[indice].restante;
        }

        tempo += executado;
        p[indice].restante -= executado;

        printf(
            "Tempo %d -> %d: P%d executou %d unidade(s). "
            "Restante: %d\n",
            inicioExecucao,
            tempo,
            p[indice].id,
            executado,
            p[indice].restante
        );

        /* Processos que chegaram durante a execucao
           entram na fila antes do retorno do processo atual. */
        while (proximo < n &&
               p[proximo].chegada <= tempo) {

            if (!enfileirar(&fila, proximo)) {
                printf("Erro ao inserir processo na fila.\n");
                return EXIT_FAILURE;
            }

            proximo++;
        }

        /* Se ainda falta executar, o processo retorna
           ao final da fila. Caso contrario, termina. */
        if (p[indice].restante > 0) {

            if (!enfileirar(&fila, indice)) {
                printf("Erro ao reinserir processo na fila.\n");
                return EXIT_FAILURE;
            }

        } else {
            p[indice].conclusao = tempo;

            p[indice].retorno =
                p[indice].conclusao - p[indice].chegada;

            p[indice].espera =
                p[indice].retorno - p[indice].burst;

            concluidos++;
        }
    }

    /* Apresenta os resultados na ordem P1, P2, P3..