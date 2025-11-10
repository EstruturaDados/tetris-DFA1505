#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Peca gerarPeca() {
    static int idCounter = 1;
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    int totalTipos = 7;
    
    p.id = idCounter++;
    p.tipo = tipos[rand() % totalTipos];
    return p;
}

int filaVazia(Fila* f) {
    return (f->quantidade == 0);
}

int filaCheia(Fila* f) {
    return (f->quantidade == TAM_FILA);
}

void enqueue(Fila* f, Peca p) {
    if (filaCheia(f)) {
        printf("ERRO: Fila cheia!\n");
        return;
    }
    f->fim = (f->fim + 1) % TAM_FILA;
    f->vetor[f->fim] = p;
    f->quantidade++;
}

Peca dequeue(Fila* f) {
    Peca p;
    p.id = -1;
    p.tipo = 'X';

    if (filaVazia(f)) {
        printf("ERRO: Fila vazia!\n");
        return p;
    }
    
    p = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
    
    printf("Inicializando a fila com %d pecas...\n", TAM_FILA);
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(f, gerarPeca());
    }
}

void mostrarFila(Fila* f) {
    printf("\n--- Fila de Pecas [Itens: %d/%d] ---\n", f->quantidade, TAM_FILA);
    
    if (filaVazia(f)) {
        printf("(Fila vazia)\n");
        printf("-------------------------------------\n");
        return;
    }

    int i = f->inicio;
    int cont;
    
    for (cont = 0; cont < f->quantidade; cont++) {
        printf("  %d. [ID: %-3d | Tipo: %c]", cont + 1, f->vetor[i].id, f->vetor[i].tipo);
        
        if (cont == 0) {
            printf(" <- PROXIMA\n");
        } else {
            printf("\n");
        }
        
        i = (i + 1) % TAM_FILA;
    }
    printf("-------------------------------------\n");
}

int main() {
    srand(time(NULL));
    Fila filaDePecas;
    int opcao = -1;

    inicializarFila(&filaDePecas);

    do {
        system("clear || cls");
        mostrarFila(&filaDePecas);

        printf("\n=== Menu Tetris Stack ===\n");
        printf("1. Jogar Peca\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (!filaVazia(&filaDePecas)) {
                    Peca jogada = dequeue(&filaDePecas);
                    printf("\nPeca [ID: %d, Tipo: %c] foi jogada.\n", jogada.id, jogada.tipo);
                    
                    Peca nova = gerarPeca();
                    enqueue(&filaDePecas, nova);
                    printf("Peca [ID: %d, Tipo: %c] entrou na fila.\n", nova.id, nova.tipo);
                } else {
                    printf("\nFila vazia, nada para jogar.\n");
                }
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
