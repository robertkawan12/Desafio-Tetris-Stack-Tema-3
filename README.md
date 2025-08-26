README.md# 🎮 Tetris Stack - Simulação de Fila de Peças

Projeto desenvolvido para simular a **fila de peças futuras** de um jogo inspirado no Tetris, utilizando **linguagem C** e o conceito de **fila circular**.

---

## 📌 Descrição

Neste projeto, implementamos um sistema que controla as peças futuras do jogo **Tetris Stack**.  
As peças possuem dois atributos principais:

-   **nome**: caractere que representa o tipo da peça (`'I'`, `'O'`, `'T'`, `'L'`).
-   **id**: número inteiro único que representa a ordem de criação da peça.

A fila é inicializada com **5 peças** geradas automaticamente. O jogador pode então:

1. **Jogar uma peça** (remoção da frente da fila - _dequeue_).
2. **Inserir nova peça** (adição ao final da fila - _enqueue_).
3. **Visualizar o estado atual da fila** a cada ação.

---

## 📂 Estrutura do Código

-   `struct Peca`: representa uma peça do jogo (`nome`, `id`).
-   `struct Fila`: representa a fila circular, armazenando as peças.
-   **Funções principais**:
    -   `inicializarFila`: prepara a fila para uso.
    -   `filaCheia` / `filaVazia`: verificam o estado da fila.
    -   `gerarPeca`: cria automaticamente uma peça com tipo aleatório e id único.
    -   `enfileirar`: adiciona uma peça ao final da fila (_enqueue_).
    -   `desenfileirar`: remove a peça da frente da fila (_dequeue_).
    -   `exibirFila`: mostra no terminal o estado atual da fila.

---

## 📊 Exemplo de Saída

```bash
=== Fila de peças ===
[T 0] [O 1] [L 2] [I 3] [I 4]

Opções de ação:
1 - Jogar peça (dequeue)
2 - Inserir nova peça (enqueue)
0 - Sair
Escolha: 1

Você jogou a peça [T 0]

=== Fila de peças ===
[O 1] [L 2] [I 3] [I 4] [T 5]
```
