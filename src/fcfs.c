#include <stdio.h>
#include <stdlib.h>
 

typedef struct {
    int id;      
    int chegada;                 
    int tempo;       
    int inicio;       
    int fim;        
    int espera;      
    int retorno;     
} Processo;
 

typedef struct No {
    Processo *proc;
    struct No *prox;
} No;
 
typedef struct {
    No *inicio;  
    No *fim;  
} Fila;
 
void iniciarFila(Fila *f) {
    f->inicio= NULL;
    f->fim = NULL;
}
 
int filaVazia(Fila *f) {
    return f->inicio == NULL;
}
 

void Insere_no_final_da_fila(Fila *f, Processo *p) {
    No *novo = malloc(sizeof(No));
    if (novo== NULL){
    printf("Erro de memoria.\n");
    }else{
    novo->proc = p;
    novo->prox = NULL;
    if (filaVazia(f)== NULL){
     f->inicio= novo;
     f->fim= novo;
    }else{ 
    f->fim->prox = novo;
    f->fim = novo;
    }
    }
}
 
Processo *Remove_do_inicio_da_fila(Fila *f) {
    if (filaVazia(f)){
     return NULL;
    }else{
    No *aux = f->inicio;
    Processo *p = aux->proc;
    f->inicio = aux->prox;
    if (f->inicio == NULL){
        f->fim = NULL;
    }
    free(aux);
    return p;
    }
}
 
void ordenarPorChegada(Processo p[], int n) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - 1 - i; j++) {
if (p[j].chegada > p[j + 1].chegada) {
Processo aux = p[j];
p[j] = p[j + 1];
p[j + 1] = aux;
}
}
}
}
 
int main(void) {
    int n;
 
    printf("=== Escalonamento FCFS ===\n");
    printf("Quantidade de processos: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }
 
    Processo *procs = malloc(n * sizeof(Processo));
    if (procs==NULL){
     printf("Erro de memoria.\n"); return 1;
    }else{
    for (int i = 0; i < n; i++) {
        printf("\nProcesso %d\n", i + 1);
        printf("  ID: ");              
         scanf("%d", &procs[i].id);
        printf("  Tempo de chegada: "); 
        scanf("%d", &procs[i].chegada);
        printf("  Burst de CPU: ");     
        scanf("%d", &procs[i].tempo);
        if (procs[i].chegada < 0 || procs[i].tempo <= 0) {
            printf("Valores invalidos (chegada >= 0 e burst > 0).\n");
            free(procs);
            return 1;
        }
    }
    }
 
    ordenarPorChegada(procs, n);
 
    Fila fila;
    iniciarFila(&fila);
    for (int i = 0; i < n; i++)
     Insere_no_final_da_fila (&fila, &procs[i]);
 

    int tempo = 0;
    int ordem[n], k = 0;
    double somaEspera = 0, somaRetorno = 0;
 
    printf("\n--- Diagrama de Gantt ---\n");
    while (!filaVazia(&fila)) {
        Processo *p = Remove_do_inicio_da_fila(&fila);
 
        
        if (tempo < p->chegada) {
            printf("[%d-%d: OCIOSO] ", tempo, p->chegada);
            tempo = p->chegada;
        }
 
        p->inicio  = tempo;
        p->fim     = tempo + p->tempo;
        p->retorno = p->fim - p->chegada;
        p->espera  = p->inicio - p->chegada;
        tempo      = p->fim;
 
        printf("[%d-%d: P%d] ", p->inicio, p->fim, p->id);
 
        ordem[k++] = p->id;
        somaEspera  += p->espera;
        somaRetorno += p->retorno;
    }
    printf("\n");
 
    
    printf("\nOrdem de execucao: ");
    for (int i = 0; i < n; i++)
    printf("P%d%s", ordem[i], i < n - 1 ? " -> " : "\n");
 
    printf("\n%-4s %-8s %-6s %-7s %-5s %-7s %-8s\n",
           "ID", "Chegada", "Burst", "Inicio", "Fim", "Espera", "Retorno");
    for (int i = 0; i < n; i++) {
        printf("P%-3d %-8d %-6d %-7d %-5d %-7d %-8d\n",
               procs[i].id, procs[i].chegada, procs[i].tempo,
               procs[i].inicio, procs[i].fim, procs[i].espera, procs[i].retorno);
    }
 
    printf("\nTempo medio de espera:  %.2f\n", somaEspera / n);
    printf("Tempo medio de retorno: %.2f\n", somaRetorno / n);
 
    free(procs);
    return 0;
}