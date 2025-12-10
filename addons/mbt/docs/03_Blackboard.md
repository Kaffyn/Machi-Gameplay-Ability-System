# Blackboard System

> **Definição:** A "Memória de Longo Prazo" da Inteligência Artificial.

---

## 1. Conceito

O **Blackboard** é um dicionário tipado e compartilhado entre todas as Tasks de uma árvore.
Tasks NÃO devem conversar entre si diretamente.
- A Task `FindTarget` escreve na variável `target`.
- A Task `MoveTo` lê a variável `target`.

Isso permite reutilizar a Task `MoveTo` para ir até um inimigo, um item ou um ponto de patrulha. Ela só se importa com a coordenada, não com a lógica de escolha.

## 2. MBTBlackboard (C++)

Implementado como `RefCounted` para ser passado por referência.

### Tipos Suportados
O editor do MBT permite definir variáveis com tipos estritos:
- `Vector2 / Vector3` (Posições)
- `Object / Node` (Alvos)
- `float / int` (Distâncias, Contadores)
- `bool` (Flags de estado)
- `StringName` (Tags ou Identificadores)

### Scopes (Escopos)
Inspirado no LimboAI, suportamos escopos para evitar colisão de nomes em IAs complexas.
- `Global`: Compartilhado entre todos os NPCs (ex: `PlayerPosition`).
- `Local`: Específico desta instância da árvore.

## 3. Integração com Editor

No painel MBT, ao selecionar uma árvore, uma aba "Blackboard" aparece.
Você define o **Plano (Plan)**: "Esta árvore ESPERA que existam as variáveis `Target` e `HomePos`".

Se você tentar rodar a árvore sem fornecer esses dados (ou Tasks que os preencham), o debugger emitirá um alerta warning.

---

_MBT — Memória Organizada._
