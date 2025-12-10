# MBT — Machi Behavior Tree

> **Status:** Draft / Specification
> **Tecnologia:** C++ (GDExtension)
> **Dependência:** MGAS (Machi Gameplay Ability System)
> **Licença:** MIT

---

## 🧠 O Cérebro do Machi

O **MBT** é um sistema de Inteligência Artificial baseado em Árvores de Comportamento (Behavior Trees), escrito em C++ nativo para máxima performance e integração profunda com a Godot Engine 4.

Enquanto o **MGAS** atua como o **CORPO** (executando habilidades, calculando atributos, replicando dados), o **MBT** atua como o **CÉREBRO** (tomando decisões táticas e estratégicas).

### Por que MBT?

1.  **Performance Nativa:** Rodar lógicas complexas de IA em GDScript para 200 inimigos pode gargalar a CPU. O MBT processa a travessia da árvore em C++.
2.  **Editor Visual Integrado:** Um painel "Machi BT" dedicado permite criar, editar e debuggar árvores visualmente, similar ao Unreal Engine ou LimboAI.
3.  **Feito para MGAS:** Tarefas nativas como `TryActivateAbility`, `CheckAttribute` e `WaitAbilityEnd` vêm prontas de fábrica.
4.  **Blackboard Tipado:** Sistema de memória seguro e escopado para evitar conflitos de variáveis.

---

## 📚 Índice da Documentação

### Fundamentos
1.  [Introdução às Behavior Trees](docs/01_Introduction.md) — O que são e por que usar?
2.  [Arquitetura C++](docs/02_Architecture.md) — Como o MBT funciona por "baixo do capô".
3.  [Manual do Editor](docs/03_Editor_Manual.md) — Guia do painel visual e ferramentas de debug.

### Componentes
4.  [Sistema de Blackboard](docs/04_Blackboard_System.md) — Gerenciamento de memória e dados.
5.  [Referência: Composites](docs/05_Composites_Reference.md) — Sequence, Selector, Parallel.
6.  [Referência: Decorators](docs/06_Decorators_Reference.md) — Inverters, Cooldowns, Tag Checks.
7.  [Referência: Leaves](docs/07_Leaves_Reference.md) — Actions, Waits, SubTrees.

### Avançado
8.  [Integração com MGAS](docs/08_MGAS_Integration.md) — O padrão Cérebro-Corpo.
9.  [Criando Tasks Customizadas](docs/09_Custom_Tasks.md) — Estendendo em C++ e GDScript.
10. [Performance & Escala](docs/10_Performance.md) — Otimizações para centenas de agentes.

---

## 🚀 Quick Start

1.  Ative o plugin em `Project Settings > Plugins`.
2.  Adicione um node `MBTPlayer` ao seu inimigo.
3.  Crie um novo Recurso `MachiBehaviorTree` no FileSystem.
4.  Abra o painel **Machi BT** (Menu Inferior) e desenhe sua lógica.
5.  Associe a árvore ao `MBTPlayer` e forneça o `AbilitySystemComponent`.

```gdscript
# Enemy.gd
@onready var mbt_player = $MBTPlayer
@onready var asc = $AbilitySystemComponent

func _ready():
    # Inicializa a IA conectando ao corpo (ASC)
    mbt_player.initialize(asc)
    mbt_player.start()
```

---

_MBT — Inteligência, não Apenas Script._
