#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5 // tamanho fixo da fila de peças

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
    int frente;  // índice do primeiro elemento
    int tras;    // índice do último elemento
    int tamanho; // quantidade atual de elementos
} Fila;

// Protótipos
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca(int id);
void enfileirar(Fila *f, Peca p);
Peca desenfileirar(Fila *f);
void exibirFila(Fila *f);

// Função principal
int main()
{
    Fila fila;
    int opcao, idAtual = 0;
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_FILA; i++)
    {
        enfileirar(&fila, gerarPeca(idAtual++));
    }

    do
    {
        printf("\n=== Fila de peças ===\n");
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (!filaVazia(&fila))
            {
                Peca removida = desenfileirar(&fila);
                printf("\nVocê jogou a peça [%c %d]\n", removida.nome, removida.id);
            }
            else
            {
                printf("\nFila vazia! Não há peça para jogar.\n");
            }
            break;

        case 2:
            if (!filaCheia(&fila))
            {
                Peca nova = gerarPeca(idAtual++);
                enfileirar(&fila, nova);
                printf("\nPeça [%c %d] inserida na fila.\n", nova.nome, nova.id);
            }
            else
            {
                printf("\nFila cheia! Não é possível inserir nova peça.\n");
            }
            break;

        case 0:
            printf("\nSaindo do jogo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Funções auxiliares

// Inicializa a fila
void inicializarFila(Fila *f)
{
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    srand(time(NULL));
}

// Verifica se a fila está cheia
int filaCheia(Fila *f)
{
    return (f->tamanho == MAX_FILA);
}

// Verifica se a fila está vazia
int filaVazia(Fila *f)
{
    return (f->tamanho == 0);
}

// Gera uma peça automaticamente
Peca gerarPeca(int id)
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; // seleciona um tipo aleatório
    Peca p;
    p.nome = tipos[indice];
    p.id = id;
    return p;
}

// Insere uma peça no final da fila (enqueue)
void enfileirar(Fila *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("\nErro: fila cheia!\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

// Remove a peça da frente da fila (dequeue)
Peca desenfileirar(Fila *f)
{
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return p;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f)
{
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }
    int i, indice;
    for (i = 0; i < f->tamanho; i++)
    {
        indice = (f->frente + i) % MAX_FILA;
        printf("[%c %d] ", f->itens[indice].nome, f->itens[indice].id);
    }
    printf("\n");
}
