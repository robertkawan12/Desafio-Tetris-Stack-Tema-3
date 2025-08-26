# 🎮 Tetris Stack - Nível 2

Este projeto expande o desafio do **Nível 1**, adicionando uma **pilha de peças reservadas** ao gerenciamento da fila circular.  
Agora o jogador pode **jogar, reservar e usar peças** dentro de uma estrutura combinada de **fila + pilha**.

---

## 📌 Descrição

O sistema gerencia duas estruturas principais:

-   **Fila de peças (queue)** → sempre cheia, com 5 elementos fixos.
-   **Pilha de reserva (stack)** → pode armazenar até 3 peças no estilo **LIFO** (último a entrar, primeiro a sair).

Cada peça possui:

-   **nome**: caractere que representa o tipo (`'I'`, `'O'`, `'T'`, `'L'`).
-   **id**: identificador único (número crescente).

### 🔹 Ações disponíveis

1. **Jogar peça** → remove a peça da frente da fila (dequeue).

    - Uma nova peça é gerada e adicionada ao final, mantendo a fila sempre cheia.

2. **Reservar peça** → move a peça da frente da fila para o **topo da pilha** (se houver espaço).

    - Também gera nova peça para o final da fila.

3. **Usar peça reservada** → remove a peça do **topo da pilha** (pop).

4. **Sair** → finaliza o programa.

---

## 📂 Estrutura do Código

-   `struct Peca` → representa cada peça (`nome`, `id`).
-   `struct Fila` → fila circular de peças futuras.
-   `struct Pilha` → pilha linear de peças reservadas.

**Funções principais**:

-   `inicializarFila` / `inicializarPilha` → preparam as estruturas.
-   `gerarPeca` → cria nova peça com tipo aleatório.
-   `enfileirar` / `desenfileirar` → manipulam a fila.
-   `empilhar` / `desempilhar` → manipulam a pilha.
-   `exibirEstado` → mostra o conteúdo da fila e da pilha.

---

## 📊 Exemplo de Saída

```bash
=== Estado atual ===
Fila de peças: [T 0] [O 1] [L 2] [I 3] [I 4]
Pilha de reserva (Topo -> Base):

Opções de Ação:
1 - Jogar peça
2 - Reservar peça
3 - Usar peça reservada
0 - Sair
Escolha: 2

Peça [T 0] reservada!

=== Estado atual ===
Fila de peças: [O 1] [L 2] [I 3] [I 4] [L 5]
Pilha de reserva (Topo -> Base): [T 0]
```
