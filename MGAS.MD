# Machi Gameplay Ability System (MGAS) - Plugin Development Design (PDD)

> **Status:** Architecture Phase
> **Reference:** Unreal Gameplay Ability System (GAS)
> **Platform:** Godot 4.5+ (GDExtension C++)

## 1. Visão Geral e Filosofia

O **MGAS** é o "Corpo" da entidade de jogo. Ele foi projetado para desacoplar completamente a **Lógica de Capacidade** (o que eu posso fazer) da **Representação Visual** (animações/vfx) e do **Controle** (Input/IA).

**Diferenciais vs Unreal GAS:**

1. **Hot-Reload GDScript:** Habilidades são scripts GDScript que herdam de classes C++. Iteração instantânea.
2. **Native Resource System:** Sem arquivos `.ini` massivos. Tudo é configurado via Inspector (`.tres`).
3. **Tags como Strings Otimizadas:** Uso de `StringName` (Hash) em vez de Structs complexas.

**Diferenciais vs LimboAI (Comparativo):**

- LimboAI é uma FSM/BT (Cérebro). MGAS é um Sistema de Atributos/Habilidades (Corpo). Eles são ortogonais.

---

## 2. Arquitetura Core (C++)

### 2.1. O Container: `MachiAbilitySystemComponent` (Node)

O coração do sistema. Deve ser anexado a qualquer `CharacterBody2D/3D`.

- **Responsabilidades:**
  - Gerenciar `GameplayTagContainer` (Tags Ativas: `State.Stunned`, `Buff.Haste`).
  - Gerenciar `AttributeSet` (Vida, Mana, Stamina).
  - Executar `GameplayAbilities` (Instanciar, Tickar, Finalizar).
  - Gerenciar `GameplayEffects` (Duration, Stacking, Expiration).
- **Signals:**
  - `ability_activated(ability_instance)`
  - `effect_applied(effect_handle)`
  - `tag_changed(tag, count)`
  - `start_ability_fail(tag)`

### 2.2. A Unidade Lógica: `MachiGameplayAbility` (Resource)

Define _uma_ ação.

- **Ciclo de Vida:**
  1. `can_activate()`: Checa Tags (BlockedTags, RequiredTags), Custo (Mana), Cooldown.
  2. `activate()`: Inicia a lógica (ex: Tocar anim, Spawnar Projetil).
  3. `commit()`: Gasta os recursos e aplica o Cooldown.
  4. `end()`: Limpeza.
- **Campos Chave:**
  - `Tags`: Identidade (`Ability.Mage.Fireball`).
  - `CancelTags`: O que ela cancela (`Ability.Stealth`).
  - `BlockTags`: O que ela impede (`Ability.Interact`).
  - `CostEffect`: GE que define o custo.
  - `CooldownEffect`: GE que define o tempo de recarga.

### 2.3. A Unidade de Dados: `MachiAttributeSet` (Resource)

Define "quem" é o personagem numericamente.

- **Estrutura Interna:** Mapas de `StringName` -> `float`.
- **Base vs Current:**
  - `BaseValue`: Valor permanente (ex: 100 de Vida Max).
  - `CurrentValue`: Valor após buffs/debuffs (ex: 100 base + 10 buff = 110).
- **Replicação:** Apenas atributos "sujos" são enviados pela rede (Bitmasking).

### 2.4. A Unidade de Mutação: `MachiGameplayEffect` (Resource)

A _única_ maneira legal de alterar Atributos ou adicionar Tags.

- **Tipos de Duração:**
  - `Instant`: Dano, Cura. (Aplica e morre).
  - `Duration`: Buff temporário (5s).
  - `Infinite`: Equipamento, Aura.
- **Modificadores:**
  - Soma (`Health += 10`)
  - Multiplicação (`Speed *= 1.5`)
  - Override (`State = Froze`)
- **Period:** Para DoT (Damage over Time) ou HoT.

---

## 3. Workflow de Desenvolvimento

1. **Criação de Atributos:** Designer cria `HeroAttributes.tres` e define `{ "Health": 100, "Mana": 50 }`.
2. **Criação de Efeitos:**
   - `GE_Damage.tres`: Instant, Health -= 10.
   - `GE_Stun.tres`: Duration 2s, Grants `State.Stunned`.
3. **Criação de Habilidade (GDScript):**
   ```gdscript
   extends MachiGameplayAbility
   func _activate():
       owner.play_anim("Attack")
       await get_tree().create_timer(0.5).timeout
       owner.apply_effect_to_target(target, damage_ge)
       end_ability()
   ```
4. **Runtime:** O Player aperta botão -> Input chama `ASC.try_activate_ability("Ability.Attack")`.

---

## 4. Roadmap de Engenharia

### Fase 1: Fundação (Atual)

- [x] Estrutura Básica GDExtension.
- [ ] Atributos Base e Current funcionais.
- [ ] Sistema de Tags Hierárquico Robusto.

### Fase 2: Ability Execution

- [ ] Instanciação de Habilidades GDScript via C++.
- [ ] Cost e Cooldown automáticos via `commit()`.
- [ ] Cancelamento automático por Tags.

### Fase 3: Effects Engine

- [ ] Stacking de Efeitos (ex: Máximo 3 stacks de veneno).
- [ ] Políticas de Refresh (Renovar duração ao reaplicar).
- [ ] Modificadores Complexos (Snapshot vs Realtime).

### Fase 4: Multiplayer (Rollback)

- [ ] Prediction de Atributos no Cliente.
- [ ] Server Correction de Habilidades.
