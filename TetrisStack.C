#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5  // tamanho fixo da fila
#define MAX_PILHA 3 // limite de peças na reserva

// Estrutura que representa uma peça do jogo
typedef struct
{
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct
{
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Estrutura da pilha
typedef struct
{
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// -------- Protótipos --------
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
Peca gerarPeca(int id);
void enfileirar(Fila *f, Peca p);
Peca desenfileirar(Fila *f);
void empilhar(Pilha *p, Peca x);
Peca desempilhar(Pilha *p);
void exibirEstado(Fila *f, Pilha *p);

// -------- Função principal --------
int main()
{
    Fila fila;
    Pilha pilha;
    int opcao, idAtual = 0;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < MAX_FILA; i++)
    {
        enfileirar(&fila, gerarPeca(idAtual++));
    }

    do
    {
        printf("\n=== Estado atual ===\n");
        exibirEstado(&fila, &pilha);

        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Jogar peça
            if (!filaVazia(&fila))
            {
                Peca jogada = desenfileirar(&fila);
                printf("\nVocê jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                // Mantém a fila cheia
                enfileirar(&fila, gerarPeca(idAtual++));
            }
            break;

        case 2: // Reservar peça
            if (!filaVazia(&fila) && !pilhaCheia(&pilha))
            {
                Peca reservada = desenfileirar(&fila);
                empilhar(&pilha, reservada);
                printf("\nPeça [%c %d] reservada!\n", reservada.nome, reservada.id);
                // Mantém a fila cheia
                enfileirar(&fila, gerarPeca(idAtual++));
            }
            else if (pilhaCheia(&pilha))
            {
                printf("\nA pilha de reserva está cheia!\n");
            }
            break;

        case 3: // Usar peça da reserva
            if (!pilhaVazia(&pilha))
            {
                Peca usada = desempilhar(&pilha);
                printf("\nVocê usou a peça reservada [%c %d]\n", usada.nome, usada.id);
            }
            else
            {
                printf("\nA pilha de reserva está vazia!\n");
            }
            break;

        case 0:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// -------- Implementação das funções --------

void inicializarFila(Fila *f)
{
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    srand(time(NULL));
}

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int filaCheia(Fila *f)
{
    return f->tamanho == MAX_FILA;
}

int filaVazia(Fila *f)
{
    return f->tamanho == 0;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

Peca gerarPeca(int id)
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    Peca p;
    p.nome = tipos[indice];
    p.id = id;
    return p;
}

void enfileirar(Fila *f, Peca p)
{
    if (filaCheia(f))
        return;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

Peca desenfileirar(Fila *f)
{
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return p;
}

void empilhar(Pilha *p, Peca x)
{
    if (pilhaCheia(p))
        return;
    p->itens[++p->topo] = x;
}

Peca desempilhar(Pilha *p)
{
    return p->itens[p->topo--];
}

void exibirEstado(Fila *f, Pilha *p)
{
    printf("Fila de peças: ");
    for (int i = 0; i < f->tamanho; i++)
    {
        int indice = (f->frente + i) % MAX_FILA;
        printf("[%c %d] ", f->itens[indice].nome, f->itens[indice].id);
    }
    printf("\n");

    printf("Pilha de reserva (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}
