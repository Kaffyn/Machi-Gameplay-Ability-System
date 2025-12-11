# Machi Behavior Tree (MBT) - Plugin Development Design (PDD)

> **Status:** Planning Phase (Not Started)
> **Reference:** LimboAI (Reverse Engineering), Unreal Behavior Tree
> **Platform:** Godot 4.5+ (GDExtension C++)

## 1. Visão Geral e Filosofia

O **MBT** é o "Cérebro". Enquanto o LimboAI é uma solução genérica excelente, o MBT foca em ser **O Driver do MGAS**. Ele abre mão de generalidade para ganhar **Integração Profunda**.

**O "Machi Way":**

- IA não toca em física. IA não toca em atributos.
- IA apenas **Lê o Blackboard** e **Requisita Habilidades (MGAS)**.

**Diferenciais vs LimboAI:**

1. **MGAS-Native:** Nós como `ActivateAbility` e `CheckGameplayTag` são cidadãos de primeira classe, não scripts custom.
2. **Performance:** Focado em _milhares_ de agentes simples (Horde AI) vs poucos agentes complexos.
3. **Editor Integrado:** O Debugger visual deve mostrar não só o fluxo da árvore, mas quais Habilidades do MGAS estão ativas no momento.

---

## 2. Engenharia Reversa: O Modelo LimboAI (Adaptado)

Analisando `addons/limboai`, vemos uma estrutura sólida que vamos mimetizar mas reescrever para nosso propósito.

### 2.1. O Executor: `MachiBTPlayer` (Node)

_Comparável ao `BTPlayer` do LimboAI._

- **Função:** Componente que ticka a árvore.
- **Behavior:**
  - `run_behavior()`: Carrega e inicia a árvore.
  - `update(delta)`: Propaga o tick da raiz para as folhas.
- **Diferença:** O nosso `BTPlayer` cacheia a referência ao `MachiASC` (Ability System) no `_ready` para evitar `get_node` repetitivo nas Tasks.

### 2.2. A Definição: `MachiBehaviorTree` (Resource)

_Comparável ao `BehaviorTree` do LimboAI._

- **Função:** Armazena a estrutura hierárquica. Serializável.
- **Feature:** Deve suportar "SubTrees" (incluir uma árvore dentro da outra) nativamente.

### 2.3. A Memória: `MachiBlackboard` (RefCounted)

_Comparável ao `Blackboard` do LimboAI._

- **Dados:** Dicionário tipado `StringName` -> `Variant`.
- **Escopo:**
  - `Local`: Válido apenas para esta árvore.
  - `Shared`: Compartilhado entre vários agentes (ex: "Alerta Global").
- **Binding:** Variáveis do Blackboard podem ser "Bindadas" para Atributos do MGAS? (Ex: `BB.Health` reflete `ASC.Health` automaticamente? Seria incrível).

### 2.4. As Tarefas: `MachiBTTask` (Object/Resource)

_Comparável ao `BTTask` do LimboAI._

Aqui reside a maior mudança. No LimboAI, Tasks são Resources.

**Core Nodes (Implementados em C++):**

- **Composites:**
  - `Selector`: OR lógico. (Tenta 1, se falhar, tenta 2).
  - `Sequence`: AND lógico. (Faz 1, depois 2).
  - `Parallel`: Roda X filhos ao mesmo tempo. (Andar E Atirar).
- **Decorators:**
  - `Cooldown`: Impede execução frequente.
  - `BlackboardCompare`: Se `Health < 50%`.
  - `TagCheck` (MGAS): Se `ASC.HasTag("Status.Stunned")` -> Bloqueia.
- **Leaves (Ações):**
  - `TryActivateAbility`: Chama `ASC.try_activate_ability(tag)`. Retorna `RUNNING` enquanto a habilidade não terminar (sinal `ability_ended`).
  - `StopAbility`: Força cancelamento.
  - `SetBlackboardValue`: Escrita na memória.

---

## 3. Workflow de Desenvolvimento

1. **Definição de Habilidades (MGAS):** Crie `GA_Attack`, `GA_Dodge`. Teste manualmente no Player.
2. **Criação da Árvore (MBT):**
   - Root -> Selector
     - Sequence (Self-Preservation)
       - Cond: `Health < 30%`
       - Action: `TryActivateAbility("Ability.Heal")`
     - Sequence (Combat)
       - Cond: `HasTarget`
       - Action: `TryActivateAbility("Ability.Attack")`
3. **Setup do NPC:** Adicione `MachiASC` e `MachiBTPlayer`. Arraste a BT para o Player.

---

## 4. Roadmap de Engenharia

### Fase 1: O Executor (Skeleton)

- [ ] Implementar `MachiBTTask` (Base).
- [ ] Implementar `MachiBTPlayer` (Ticker).
- [ ] Implementar `Selector` e `Sequence` (Lógica sequencial simples).

### Fase 2: Integração de Dados (Blackboard)

- [ ] Sistema de variáveis tipadas.
- [ ] Inspetor customizado para editar Blackboard padrão na Scene.

### Fase 3: A Ponte MGAS

- [ ] Criar Task `ActivateAbility`. Isso exige ouvir sinais do ASC em C++.
- [ ] Criar Decorator `HasGameplayTag`.

### Fase 4: O Editor (Workbench)

- [ ] Copiar/Adaptar GraphEdit do LimboAI (Reverse Engineering UI).
- [ ] Criar visualização de Nodes customizada.
- [ ] Debugger colorido em tempo real.
