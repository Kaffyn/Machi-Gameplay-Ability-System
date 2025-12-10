# 03. Manual do Editor Visual

> **Contexto:** Guia de uso do painel "Machi BT" dentro da Godot.

---

## Interface Principal

Ao selecionar um arquivo `.mbt` (ou Resource `MachiBehaviorTree`) no FileSystem ou clicar em um node `MBTPlayer`, o painel inferior (Bottom Panel) do editor se expande.

### 1. A Área de Grafo (Canvas)
- **Navegação:**
  - `Botão do Meio / Espaço + Click`: Pan.
  - `Roda do Mouse`: Zoom.
- **Manipulação:**
  - `Click e Arraste`: Move nós.
  - `Shift + Click`: Seleção múltipla.
  - `Del`: Deleta nós selecionados.

### 2. A Paleta de Tarefas (Task Palette)
Localizada à esquerda (ou popup no `Right Click`).
Categorias:
- **Composites:** Vermelho. (Sequence, Selector).
- **Decorators:** Amarelo. (Inverter, VerifyTag).
- **Leaves (Actions):** Azul. (ActivateAbility, Wait).
- **Leaves (Conditions):** Verde. (IsTargetSeen).

### 3. O Inspetor de Tarefas
Ao clicar em um nó no grafo, o Inspetor nativo da Godot (lado direito) exibe as propriedades daquela Task.
Exemplo: Ao clicar em `Wait`, você vê a propriedade `Time` (float).

### 4. O Editor de Blackboard
Uma aba secundária no painel. Permite definir as **Variáveis Esperadas** (Plan) para esta árvore.
- Botão `+ Add Variable`: Cria uma nova entrada.
- Colunas: `Name` (String), `Type` (Vector3, Object, Float), `Default Value`.

---

## Fluxo de Criação

1.  **Criar Root:** Toda árvore começa com um nó Root (automaticamente criado ou adicionado manualmente). Ele só aceita 1 filho.
2.  **Adicionar Lógica:** Clique com botão direito -> `Add Composite` -> `Selector`. Conecte o Root ao Selector.
3.  **Ramificar:** Do Selector, puxe conexões para criar ramos de prioridade (ex: `Combat` à esquerda, `Idle` à direita).
4.  **Adicionar Decorators:** Para adicionar uma condição (ex: "Só ataque se ver o player"), clique com botão direito no nó de Ataque -> `Add Decorator`. O Decorator "abraçará" o nó.

---

## Debugger em Tempo Real

Quando o jogo roda:
1.  Selecione o NPC na aba "Remote" da Scene Tree.
2.  O Editor Visual do MBT se conectará à instância rodando.
3.  **Color Coding:**
    - 🟢 **Verde:** Caminho de Sucesso (Executando agora).
    - 🔴 **Vermelho:** Falhou.
    - 🟡 **Amarelo:** Running (Ação em andamento).
4.  **Variáveis:** O painel de Blackboard mostra os valores em tempo real (`Target: Player(ID:1234)`).

---

_Próximo: [Sistema de Blackboard](04_Blackboard_System.md)_
