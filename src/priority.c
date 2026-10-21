struct Processo {
    int id;
    int chegada;
    int burst;
    int prioridade;
};

int escolherProcesso(struct Processo processos[], int n, int concluidos[], int tempo) {
    int escolhido = -1;

    for (int i = 0; i < n; i++) {
        if (concluidos[i] == 0 && processos[i].chegada <= tempo){

            if (processos[i].prioridade < processos[escolhido].prioridade) {
                escolhido = i;
            }
        }
    }

    return escolhido;
}

