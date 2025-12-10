# BehaviorStates — Vision (Evolved to MGAS)

> **Framework de Habilidade e Gameplay Next-Gen para Godot 4.x**
>
> Um sistema orientado a dados que traz o poder do Unreal GAS para o ecossistema Godot via GDExtension.

---

## Filosofia: "Engine in C++, Gameplay in Script"

O desenvolvimento de jogos AAA exige um equilíbrio delicado:
1. **Engine (C++):** Sistemas de baixo nível que rodam milhões de vezes (física, replicação, queries de tags).
2. **Gameplay (Script):** Lógica que muda constantemente e precisa de iteração rápida (habilidades, balanceamento).

O MGAS respeita essa divisão sagrada.

---

## Princípios Fundamentais

### 🔬 Princípio da Performance Híbrida

GDScript é excelente, mas não para iterar sobre 500 buffs a cada frame em 50 zumbis.
O MGAS move o "Number Crunching" (cálculo de atributos, cooldowns, tags) para C++, deixando o GDScript livre para lidar apenas com eventos de alto nível (`OnAbilityActivated`).

### 🔧 Princípio da Replicação Preditiva

Multiplayer não é um "add-on". É fundação.
O MGAS implementa **Client-Side Prediction** nativamente. O cliente executa a habilidade instantaneamente, e o sistema cuida da reconciliação se o servidor discordar. Isso elimina a sensação de "lag" em jogos rápidos.

### 🔗 Princípio da Composição Modular

Jogos não são feitos de herança (`class FireWizard extends Wizard`). São feitos de composição.
Um personagem é apenas um container de:
- **Abilities (Ações):** O que ele pode fazer.
- **Attributes (Dados):** O que ele é (HP, Mana).
- **Tags (Estado):** Como ele está (Stunned, Flying).

---

## O que Mudou? (BehaviorStates vs MGAS)

| Antes (BehaviorStates) | Agora (MGAS)          | Motivo                                                                          |
| :--------------------- | :-------------------- | :------------------------------------------------------------------------------ |
| **Fim do Compose**     | **Granted Abilities** | `Compose` era rígido. Abilities agora são concedidas/removidas dinamicamente.   |
| **Machine (GDScript)** | **ASC (C++)**         | Performance crítica e replicação de rede exigem C++.                            |
| **State Resource**     | **GameplayAbility**   | `State` era apenas visual/lógica. `GA` inclui custo, cooldown e fluxo de rede.  |
| **Effect Resource**    | **GameplayEffect**    | `Effect` agora suporta matemática complexa e modificadores de atributos em C++. |

---

## Comparativo de Arquitetura

| Métrica       | Framework Tradicional   | MGAS (GAS-like)                   |
| :------------ | :---------------------- | :-------------------------------- |
| **Cooldowns** | Timer nodes individuais | TimerManager centralizado (C++)   |
| **Buffs**     | Arrays de scripts       | ActiveEffectContainer (Otimizado) |
| **Tags**      | Strings ou Enums        | GameplayTags (Fast Hash)          |
| **Netcode**   | RPCs manuais            | Replication Graph & Prediction    |

---

## Documentação Relacionada

| Documento                         | Conteúdo                                 |
| :-------------------------------- | :--------------------------------------- |
| [README.md](README.md)            | Quickstart e visão geral                 |
| [API Reference](API_REFERENCE.md) | Contratos formais da API C++             |
| [Architecture](Architecture.md)   | Diagramas e fluxos de comunicação        |
| [Internals](Internals.md)         | Detalhes de implementação do GDExtension |

---

_MGAS — O Futuro da Engenharia de Gameplay na Godot._
