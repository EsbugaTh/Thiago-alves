#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura que representa uma peça
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Constantes de tamanho
#define TAM_FILA 5
#define TAM_PILHA 3

// Fila circular
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, totalFila = 0;

// Pilha linear
Peca pilha[TAM_PILHA];
int topo = -1;

// Contador global de peças criadas
int contadorID = 0;

// Gera uma nova peça com tipo aleatório
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Insere peça na fila circular
void enfileirar(Peca p) {
    if (totalFila < TAM_FILA) {
        fila[fim] = p;
        fim = (fim + 1) % TAM_FILA;
        totalFila++;
    }
}

// Remove peça da fila circular
Peca desenfileirar() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    totalFila--;
    return removida;
}

// Insere peça na pilha
int empilhar(Peca p) {
    if (topo < TAM_PILHA - 1) {
        pilha[++topo] = p;
        return 1;
    }
    return 0;
}

// Remove peça da pilha
Peca desempilhar() {
    return pilha[topo--];
}

// Exibe estado atual das estruturas
void exibirEstado() {
    printf("\nEstado atual:\n");
    printf("Fila de peças\t");
    for (int i = 0; i < totalFila; i++) {
        int idx = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }

    printf("\nPilha de reserva\t(Topo -> base): ");
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// Troca peça da frente da fila com topo da pilha
void trocarAtual() {
    if (topo >= 0 && totalFila > 0) {
        int idx = inicio;
        Peca temp = fila[idx];
        fila[idx] = pilha[topo];
        pilha[topo] = temp;
    }
}

// Troca múltipla entre fila e pilha
void trocaMultipla() {
    if (topo >= 2 && totalFila >= 3) {
        for (int i = 0; i < 3; i++) {
            int idx = (inicio + i) % TAM_FILA;
            Peca temp = fila[idx];
            fila[idx] = pilha[topo - i];
            pilha[topo - i] = temp;
        }
        printf("\nAção: troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
    } else {
        printf("\nNão há peças suficientes para troca múltipla.\n");
    }
}

// Menu principal
int main() {
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    while (totalFila < TAM_FILA) {
        enfileirar(gerarPeca());
    }

    int opcao;
    do {
        exibirEstado();
        printf("\nCódigo\tAção\n");
        printf("1\tJogar peça da frente da fila\n");
        printf("2\tEnviar peça da fila para a pilha de reserva\n");
        printf("3\tUsar peça da pilha de reserva\n");
        printf("4\tTrocar peça da frente da fila com o topo da pilha\n");
        printf("5\tTrocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0\tSair\n");
        printf("\nOpção escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (totalFila > 0) {
                    desenfileirar();
                    enfileirar(gerarPeca());
                }
                break;
            }
            case 2: {
                if (totalFila > 0 && topo < TAM_PILHA - 1) {
                    Peca p = desenfileirar();
                    empilhar(p);
                    enfileirar(gerarPeca());
                } else {
                    printf("\nNão foi possível reservar a peça.\n");
                }
                break;
            }
            case 3: {
                if (topo >= 0) {
                    desempilhar();
                } else {
                    printf("\nNão há peças na pilha para usar.\n");
                }
                break;
            }
            case 4: {
                trocarAtual();
                break;
            }
            case 5: {
                trocaMultipla();
                break;
            }
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

