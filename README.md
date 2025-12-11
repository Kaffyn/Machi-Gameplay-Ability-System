# Machi Plugin Suite

> **Engenharia de Jogos de Alta Performance para Godot Engine**

Este documento serve como a referência técnica primária para a arquitetura do **Machi Plugin Suite**. Ele detalha como os sistemas **MGAS** (Gameplay Ability System) e **MBT** (Behavior Tree) operam, interagem e devem ser utilizados para criar jogos de alta complexidade no Godot 4.5+.

---

## 🏛️ Filosofia da Arquitetura

O Machi Suite foi construído sobre três pilares de engenharia:

1. **Hybrid C++ / GDScript (GDExtension):**

   - **C++ (Engine Tier):** A "máquina pesada" roda aqui. Simulação de atributos, iteração de behavior trees, replicação de rede e sistemas de tags. Focado em performance de memória e CPU.
   - **GDScript (Gameplay Tier):** A lógica de jogo vive aqui. Designers e Programadores estendem classes C++ (`MachiGameplayAbility`, `BTTask`) para implementar regras específicas do jogo com iteração rápida.

2. **Resource-Oriented Programming (ROP):**

   - Dados comportam-se como objetos. `Abilities`, `Effects`, `SkillTrees` e `BehaviorTrees` são todos arquivos `.tres` (Resources). Isso permite edição fácil no Inspector, versionamento via Git e injeção de dependência.

3. **Entity Component System (ECS-Lite):**
   - Não puro ECS, mas com forte separação. A entidade (`CharacterBody2D`) é apenas um container. A lógica real reside nos Componentes (`AbilitySystemComponent`) e nos Dados (`AttributeSet`).

---

## ⚔️ Módulo 1: Machi Gameplay Ability System (MGAS)

**O "Corpo" (Capability & State)**

O MGAS gerencia **o que** uma entidade pode fazer (Abilities) e **seu estado atual** (Attributes, Tags).

### 1.1 Core Components

#### `MachiAbilitySystemComponent` (Node)

O cérebro do MGAS. Deve ser adicionado a qualquer ator que use habilidades.

- **Função:** Gerencia Tags ativas, lista de Habilidades concedidas e aplica Efeitos.
- **API Chave:** `try_activate_ability(tag)`, `apply_gameplay_effect_to_self(ge)`.

#### `MachiAttributeSet` (Resource)

Define os dados numéricos da entidade (Health, Mana, Speed).

- **Base Value vs Current Value:** Separação entre valor "puro" e valor modificado temporariamente.
- **Dirty Bitmask:** Para replicação eficiente, apenas atributos alterados trafegam na rede.

### 1.2 Resource Types

#### `MachiGameplayAbility` (GA)

Uma ação performável. Pode ser instantânea (Pulo) ou duradoura (Canalizar Magia).

- **Tags:**
  - `Ability Tags`: Identidade da habilidade (ex: `Ability.Attack.Fire`).
  - `Cancel Tags`: O que ela cancela ao iniciar (ex: `Ability.Stealth`).
  - `Block Tags`: O que ela impede enquanto ativa (ex: `Ability.Action`).
- **Flow:** `should_activate()` -> `activate()` -> `commit()` (custo/CD) -> `end()`.

#### `MachiGameplayEffect` (GE)

A unidade de mudanças de estado. **Abilities não mudam atributos diretamente; elas aplicam Effects.**

- **Duration:** Instantâneo, Duração Fixa ou Infinito.
- **Modifiers:** Operações matemáticas (`Add`, `Multiply`, `Override`) em Atributos.
- **Granted Tags:** Tags que o efeito "cola" no ator enquanto ativo (ex: `State.Stunned`).

---

## 🧠 Módulo 2: Machi Behavior Tree (MBT)

**O "Cérebro" (Decision & Control)**

O MBT decide **quando** e **como** usar as capacidades do MGAS. Ele não move o personagem diretamente; ele envia intenções.

### 2.1 Editor Visual (The Workbench)

O plugin adiciona um painel dedicado ("Machi MBT") ao editor.

- **Canvas:** Grafo visual de nós.
- **Blackboard Panel:** Define a "memória" da IA (alvo atual, última posição vista).
- **Live Debugger:** Conecta-se automaticamente a instâncias rodando.
  - 🟢 **Verde:** Sucesso (Nó ativo ou concluído OK).
  - 🔴 **Vermelho:** Fracasso (Condição não atendida).
  - 🟡 **Amarelo:** Running (Ação em progresso, ex: esperando animação).

### 2.2 Node Architecture

#### `Composites` (Controle de Fluxo)

- **Selector (?):** Tenta filhos em ordem até um ter sucesso. "Faça A, se não der, faça B". Prioridade.
- **Sequence (->):** Executa filhos em ordem. Falha se algum falhar. "Faça A, E DEPOIS B". Lógica sequencial.

#### `Decorators` (Condicionais)

"Envelopam" um nó para adicionar lógica antes/depois.

- **BlackboardVerify:** "Só execute se a variável `HasTarget` for true".
- **Cooldown:** "Só permita execuções a cada X segundos".

#### `Leaves` (Ações e Queries)

Os nós de ponta que fazem o trabalho sujo.

- **ActivateAbility (MGAS Integration):** Pede ao ASC para ativar uma habilidade por Tag. Retorna `RUNNING` enquanto a habilidade durar.
- **Wait:** Espera X segundos.

---

## � Integração: O Padrão "Action Request"

A maior força da suite é como eles se integram. **A IA (MBT) nunca deve alterar `hp` diretamente.**

1. **Percepção:** Sensores populam o **Blackboard** da MBT (`Target = Player`).
2. **Decisão:** A MBT navega o grafo (Sequence: Tem Alvo? -> Está Perto? -> Atacar).
3. **Requisição:** O nó folha `ActivateAbility` chama `ASC.try_activate_ability("Ability.Melee")`.
4. **Execução (MGAS):**
   - O MGAS checa: Tenho mana? Estou stunado (`State.Stunned`)? O cooldown acabou?
   - Se OK: Toca animação, aplica dano (via GameplayEffect).
   - Se Falhar: Retorna `FALSE`, e a MBT tenta o próximo ramo (ex: Fugir).

---

## 📂 Organização Recomendada

```text
res://
├── addons/mgas/ & addons/mbt/   # Plugins Core (Não toque)
├── bin/                         # Binários GDExtension
├── project_name/
    ├── abilities/               # Seus MachiGameplayAbilities (.tres)
    ├── effects/                 # Seus MachiGameplayEffects (.tres)
    ├── behaviors/               # Seus MachiBehaviorTrees (.tres)
    ├── attributes/              # Seus AttributeSets Customizados
    └── entities/                # Cenas (.tscn) com ASC e MBT Player
```

Para detalhes de API, consulte:

- [MGAS API Reference](addons/mgas/docs/09_API_Reference.md)
- [MBT Node Reference](addons/mbt/docs/05_Composites_Reference.md)
