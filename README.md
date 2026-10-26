# Projeto: Algoritmos de Escalonamento - Sistemas Operacionais

Este é um projeto da disciplina de **Sistemas Operacionais** do curso de Análise e Desenvolvimento de Sistemas, do IF Baiano Campus Guanambi.

# Projeto de Escalonamento de Processos

## Sobre o projeto

Este projeto tem como objetivo implementar algoritmos de escalonamento de processos utilizados em Sistemas Operacionais, permitindo compreender como o sistema seleciona e organiza a execução dos processos.

## Algoritmos

- **FCFS (First Come, First Served):** executa os processos na ordem de chegada.
- **SJF (Shortest Job First):** prioriza o processo disponível com menor tempo de execução.
- **Round Robin (RR):** distribui o tempo de CPU entre os processos por meio de fatias de tempo.
- **Priority Scheduling:** seleciona o processo disponível de acordo com sua prioridade.

## Tecnologias utilizadas

- Linguagem C
- Compilador GCC
- Padrão C11

## Como compilar e executar

Exemplo para compilar o algoritmo de prioridade:

```bash
gcc -Wall -Wextra -pedantic -std=c11 -g src/priority.c -o priority
```

Para executar:

```bash
./priority
```

O programa solicita a quantidade de processos e os dados de cada processo, como tempo de chegada, tempo de execução e prioridade.

## Escalonamento por prioridade

Na implementação não preemptiva, o processo selecionado continua executando até terminar. Entre os processos disponíveis, é escolhido aquele com maior prioridade. Nesta implementação, um número menor representa uma prioridade maior.

Em caso de empate na prioridade, é considerado primeiro o processo que chegou antes.

## O grupo é composto por:

*Raissa Gomes Carneiro* </br>
*Fernanda Amille Pereira Santos* </br>
*Fernanda Magalhães de Souza* </br>
*Enzo Gabriel Lima Dias* </br>
*Anthony Viana dos Santos* </br>

