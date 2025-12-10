# 07. Referência: Leaves (Folhas)

> **Função:** Ações e Condições. Não têm filhos.

---

## Ações Genéricas

### `Wait`
Espera por X segundos. Retorna RUNNING durante a espera, e SUCCESS ao terminar.
- **Random Deviation:** Pode adicionar aleatoriedade (ex: esperar entre 1.0s e 1.5s).

### `Print` / `Log`
Imprime uma string no console da Godot. Útil para debug da árvore.

### `RunSubtree`
Executa outro arquivo `MachiBehaviorTree`. Promove modularidade.
- Ex: Um arquivo `CombatTree.tres` pode ser usado dentro da árvore `MainTree.tres`.

---

## Ações MGAS (Integração)

### `TryActivateAbility`
Tenta ativar uma Habilidade do MGAS pela Tag.
- **Parâmetros:** `Tag` (StringName), `WaitFinish` (bool).
- **Comportamento:**
  - Se `WaitFinish = true`: Retorna RUNNING até receber o sinal `ability_ended`.
  - Se `WaitFinish = false`: Retorna SUCCESS assim que a habilidade é ativada ("Fire and Forget").

### `CancelAbility`
Força o cancelamento de habilidades com certa Tag.

### `SetAttribute` / `AddAttribute`
Altera valores no `AttributeSet` do NPC (Cheat/Scripted event).

---

## Condições (Queries)

### `CompareAttribute`
Compara um atributo do MGAS com um valor.
- Ex: `Health < 50%`.

### `QueryGameplayTags`
Verifica contagem de Tags.

---

_Próximo: [Integração com MGAS](08_MGAS_Integration.md)_
