# 08. Integração MGAS (Deep Dive)

> **Regra de Ouro:** O MBT apenas aperta os botões. O MGAS faz a mágica.

---

## O Fluxo de Controle

1.  **Percepção (Blackboard):**
    Sensores (Area2D, Raycast) atualizam o Blackboard. "Inimigo à vista na pos (10, 0)".
2.  **Decisão (MBT):**
    A árvore avalia: `TemInimigo?` -> `Sim`. `HP > 10%?` -> `Sim`. `Cooldown BolaFogo?` -> `Ok`.
    Ação escolhida: `ActivateAbility("Skill.Fireball")`.
3.  **Execução (MGAS):**
    O `AbilitySystemComponent` recebe o pedido.
    - Checa Stamina.
    - Checa se não está Stunado (`BlockTags`).
    - Spawna o projétil.
    - Aplica o Cooldown (`CooldownTags`).
4.  **Feedback (MBT):**
    Se a habilidade falhou (ex: sem mana), a Task retorna `FAILURE`.
    O nó Selector do MBT tenta a próxima opção: `ActivateAbility("Skill.Melee")`.

## Por que separar?

Imagine programar um Boss "Dragão".

**Sem MGAS:**
Na árvore, você teria Tasks gigantes: `VoarECuspirFogo`. Dentro dela, 500 linhas de código controlando animação no AnimationPlayer, movendo o CharacterBody, detectando colisão, tocando som...

**Com MGAS:**
Na árvore, a Task é simples: `ActivateAbility("Dragon.FlyBreath")`.
A lógica do voo, do fogo e do dano está isolada dentro de uma **GameplayAbility** (script separado ou blueprint).

Isso permite:
1.  **Testar a habilidade sem a IA:** O dev pode apertar um botão de debug e fazer o dragão cuspir fogo, sem precisar "convencer" a árvore de decisão a fazer isso.
2.  **Reutilizar:** Outro dragão pode usar a mesma Habilidade, mas ter uma árvore de comportamento diferente (mais agressiva ou covarde).

---

## Sinais Importantes

O MBT escuta automaticamente sinais do MGAS para gerenciar o estado `RUNNING`:

- `ability_activated(ability)`: A Task entra em estado de espera.
- `ability_ended(ability)`: A Task conclui com SUCCESS.
- `ability_failed`: (Conceitual) A Task conclui com FAILURE.

---

_Próximo: [Criando Tasks Customizadas](09_Custom_Tasks.md)_
