# Integração MBT + MGAS

> **Filosofia:** O MBT decide O QUE fazer. O MGAS decide COMO fazer.

---

## 1. O Padrão "Action Request"

Em sistemas legados, a AI acessa diretamente o CharacterController:
`npc.velocity = Vector2(100, 0)` ❌ **Errado no MGAS.**

No ecossistema Machi, a AI envia **Requests**:
`npc.ability_system.try_activate_ability("Ability.Move")` ✅ **Correto.**

Isso desacopla a IA da física. Se o NPC estiver "Stunned" (Tag no MGAS), a habilidade falha automaticamente, e a Behavior Tree recebe `FAILURE`, podendo reagir (ex: tocar som de "Ugh!").

## 2. Tasks Nativas do MGAS

O MBT vem com Tasks C++ otimizadas para interagir com o `MachiAbilitySystemComponent`:

### `BTTask_ActivateAbility`
- **Parâmetros:** `ability_tag` (StringName).
- **Comportamento:**
  1. Chama `asc->try_activate_ability(tag)`.
  2. Retorna `RUNNING` enquanto a habilidade estiver ativa.
  3. Retorna `SUCCESS` quando a habilidade termina (`end_ability`).
  4. Retorna `FAILURE` se a ativação falhou (cooldown, custo, tags).

### `BTDecorator_HasTag`
- **Parâmetros:** `tag` (StringName), `check_type` (HasAny, HasAll).
- **Comportamento:**
  - Bloqueia a execução do ramo se o NPC não tiver a Tag especificada (ou se TIVER, dependendo da configuração).
  - Útil para: `HasTag(State.Dead) -> Inverter -> Sequence(Atacar)`. (Só ataca se NÃO estiver morto).

### `BTTask_SetAttribute`
- **Parâmetros:** `attribute_name`, `value`.
- **Uso:** AI "Cheat" ou setup de cenário. Ex: Boss entra em Rage Mode e ganha 1000 de Mana instantâneo.

## 3. Exemplo de Árvore de Combate

```text
ROOT (Selector)
├── Sequence (Panic)
│   ├── HasTag("Status.LowHealth")
│   └── ActivateAbility("Ability.Flee")
│
├── Sequence (Attack)
│   ├── Decorator: Cooldown("Ability.Fireball") (Checagem local da BT)
│   ├── IsTargetVisible() (Check Blackboard)
│   └── ActivateAbility("Ability.Fireball")
│
└── ActivateAbility("Ability.Idle")
```

---

_MBT — Integração Total._
