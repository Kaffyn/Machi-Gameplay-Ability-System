# 01. Introdução às Behavior Trees

> **Nível:** Iniciante
> **Prerequisito:** Lógica de Programação Básica

---

## O que é uma Behavior Tree?

Uma **Behavior Tree (BT)** é um modelo matemático para execução de tarefas baseado em estruturas de árvore hierárquica. Diferente de uma Máquina de Estados Finita (FSM), onde você define *transições* complexas entre estados ("Se estou Idle e vejo Player, vou para Chase"), na BT você define *regras de avaliação*.

Pense na BT como uma **Checklist de Prioridades** que roda a cada frame (ou tick).

### O Fluxo de Execução (The Tick)

A cada atualização da IA (`tick`), o sinal de execução entra pela **Raiz (Root)** e flui para baixo pelos ramos, seguindo regras específicas de cada nó, até atingir uma folha (Ação).

Os nós retornam um **Status** para o pai:
1.  🟢 **SUCCESS:** "Terminei o que tinha pra fazer com sucesso."
2.  🔴 **FAILURE:** "Não consegui fazer, ou a condição é falsa."
3.  🟡 **RUNNING:** "Estou fazendo ainda, me chame de novo no próximo frame."

---

## Tipos de Nós (Nodes)

Uma BT é composta por três categorias principais de nós:

### 1. Composites (Gerentes)
Eles têm filhos e decidem *qual* filho executar.
- **Sequence (`->`):** Executa filhos em ordem. Para se um falhar. "Faça A, E B, E C". (Ex: `WalkToDoor -> OpenDoor -> WalkThrough`)
- **Selector (`?`):** Executa filhos em ordem. Para se um tiver sucesso. "Tente A, OU B, OU C". (Ex: `Attack ? Chase ? Patrol`)

### 2. Decorators (Fiscais)
Eles têm apenas UM filho e modificam seu comportamento ou resultado.
- **Inverter:** Transforma Sucesso em Falha e vice-versa (NOT).
- **Repeat:** Repete o filho X vezes.
- **Cooldown:** Só deixa o filho rodar se passou um tempo X.
- **BlackboardCheck:** Só deixa o filho rodar se a variável `HasAmmo` for true.

### 3. Leaves (Operários)
Eles não têm filhos. É onde a ação acontece.
- **Action:** Move o boneco, ataca, toca som.
- **Condition:** Verifica algo instantâneo (IsEnemyVisible?) e retorna Sucesso/Falha.

---

## Por que não usar State Machine (FSM)?

Para IAs simples (Goomba do Mario), FSM é ótima. Mas para IAs complexas, FSM vira um "Espaguete":
- Adicionar um estado "Stunned" exige criar transições de *todos* os outros estados para "Stunned".
- Na BT, você apenas coloca um Decorator na raiz ou um Selector de prioridade alta:
  ```text
  ROOT (Selector)
  ├── IsStunned? -> PlayStunAnim (Prioridade Máxima)
  ├── IsDead? -> PlayDeathAnim
  └── CombatLogic...
  ```
- BTs são **Modulares** e **Reutilizáveis**. Você pode pegar o ramo "Patrol" e colar em 10 inimigos diferentes.

---

## O Modelo Mental do MBT

No Machi Behavior Tree, a filosofia é:
**"A Árvore decide a Intenção, o MGAS executa a Ação."**

Você raramente verá uma Task `MoveAndSlide` no MBT.
Você verá uma Task `ActivateAbility("Move")`, e o MGAS cuidará da física, colisão e animação.

---

_Próximo: [Arquitetura C++](02_Architecture.md)_
