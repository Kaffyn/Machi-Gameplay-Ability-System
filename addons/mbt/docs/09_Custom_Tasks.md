# 09. Tasks Customizadas

> **Extensibilidade:** Você não está limitado aos nós que vêm com o plugin.

---

## Opção A: GDScript (Rápido e Fácil)

Para 90% dos casos de gameplay específico (ex: "Escolher melhor cobertura"), use GDScript.

1.  Crie um novo script que herde de `BTAction` (ou `BTTask`).
2.  Salve na pasta do seu projeto.
3.  Ele aparecerá automaticamente na Paleta do MBT.

```gdscript
# tasks/choose_cover.gd
extends BTAction
class_name BTChooseCover

@export var search_radius: float = 100.0

# Chamado a cada tick enquanto a task roda
func _tick(delta: float, actor: Node, blackboard: MBTBlackboard) -> int:
    var cover = find_best_cover(actor.global_position, search_radius)
    
    if cover:
        blackboard.set_var("cover_pos", cover.global_position)
        return SUCCESS
    
    return FAILURE
```

### Status Enums
- `SUCCESS` (0)
- `FAILURE` (1)
- `RUNNING` (2)

---

## Opção B: C++ GDExtension (Alta Performance)

Para Tasks genéricas e pesadas (ex: Pathfinding complexo, Matemática vetorial intensa), estenda o plugin em C++.

1.  Adicione arquivos `.h` e `.cpp` em `addons/mbt/src/tasks/`.
2.  Herde de `MBTTask`.
3.  Registre no `register_types.cpp`.
4.  Recompile o plugin.

```cpp
// mbt_task_heavy_math.cpp
int MBTTaskHeavyMath::execute(double delta, Node* actor, MBTBlackboard* blackboard) {
    // Cálculos C++ super rápidos
    if (result_ok) {
        return BT_SUCCESS;
    }
    return BT_FAILURE;
}
```

---

## Dicas de Design

- **Mantenha as Tasks Atômicas:** Evite criar uma Task "FazerTudo". Quebre em "Achar", "Mover", "Agir".
- **Use o Blackboard:** Não guarde estado dentro da Task (ela é um Resource compartilhado!). Guarde no Blackboard ou no Actor.
- **Exponha Variáveis:** Use `@export` para tornar parâmetros ajustáveis no Editor Visual.

---

_Próximo: [Performance](10_Performance.md)_
