#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura de peça
typedef struct
{
    char nome;
    int id;
} Peca;

// Variáveis globais
int contadorID = 0; // gera IDs únicos

// ---------- Função de geração de peça ----------
Peca gerarPeca()
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// ---------- Fila circular ----------
typedef struct
{
    Peca dados[MAX_FILA];
    int frente, tras, tamanho;
} Fila;

void inicializarFila(Fila *f)
{
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    for (int i = 0; i < MAX_FILA; i++)
    {
        f->dados[i] = gerarPeca();
        f->tras = (f->tras + 1) % MAX_FILA;
        f->tamanho++;
    }
}

int filaCheia(Fila *f)
{
    return f->tamanho == MAX_FILA;
}

int filaVazia(Fila *f)
{
    return f->tamanho == 0;
}

Peca removerFila(Fila *f)
{
    Peca removida = f->dados[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return removida;
}

void adicionarFila(Fila *f, Peca p)
{
    if (!filaCheia(f))
    {
        f->tras = (f->tras + 1) % MAX_FILA;
        f->dados[f->tras] = p;
        f->tamanho++;
    }
}

// ---------- Pilha ----------
typedef struct
{
    Peca dados[MAX_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

void push(Pilha *p, Peca x)
{
    if (!pilhaCheia(p))
    {
        p->dados[++p->topo] = x;
    }
}

Peca pop(Pilha *p)
{
    return p->dados[p->topo--];
}

Peca topo(Pilha *p)
{
    return p->dados[p->topo];
}

// ---------- Exibição ----------
void exibirEstado(Fila *f, Pilha *p)
{
    printf("\n=== Estado Atual ===\n");
    printf("Fila de pecas: ");
    int i, idx;
    idx = f->frente;
    for (i = 0; i < f->tamanho; i++)
    {
        printf("[%c %d] ", f->dados[idx].nome, f->dados[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
    printf("\nPilha de reserva (Topo -> Base): ");
    for (i = p->topo; i >= 0; i--)
    {
        printf("[%c %d] ", p->dados[i].nome, p->dados[i].id);
    }
    printf("\n=====================\n");
}

// ---------- Menu ----------
int main()
{
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    do
    {
        exibirEstado(&fila, &pilha);
        printf("\nOpcoes:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        { // Jogar peça
            if (!filaVazia(&fila))
            {
                Peca jogada = removerFila(&fila);
                printf("Jogou peca [%c %d]\n", jogada.nome, jogada.id);
                adicionarFila(&fila, gerarPeca());
            }
            break;
        }
        case 2:
        { // Reservar peça
            if (!filaVazia(&fila) && !pilhaCheia(&pilha))
            {
                Peca reservada = removerFila(&fila);
                push(&pilha, reservada);
                printf("Reservou peca [%c %d]\n", reservada.nome, reservada.id);
                adicionarFila(&fila, gerarPeca());
            }
            break;
        }
        case 3:
        { // Usar peça da pilha
            if (!pilhaVazia(&pilha))
            {
                Peca usada = pop(&pilha);
                printf("Usou peca [%c %d]\n", usada.nome, usada.id);
            }
            break;
        }
        case 4:
        { // Trocar frente da fila com topo da pilha
            if (!filaVazia(&fila) && !pilhaVazia(&pilha))
            {
                Peca temp = fila.dados[fila.frente];
                fila.dados[fila.frente] = pilha.dados[pilha.topo];
                pilha.dados[pilha.topo] = temp;
                printf("Troca realizada entre frente da fila e topo da pilha.\n");
            }
            break;
        }
        case 5:
        { // Trocar 3 primeiros da fila com os 3 da pilha
            if (fila.tamanho >= 3 && pilha.topo >= 2)
            {
                for (int i = 0; i < 3; i++)
                {
                    int idx = (fila.frente + i) % MAX_FILA;
                    Peca temp = fila.dados[idx];
                    fila.dados[idx] = pilha.dados[pilha.topo - i];
                    pilha.dados[pilha.topo - i] = temp;
                }
                printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
            }
            break;
        }
        }
    } while (opcao != 0);

    return 0;
}
