# 04. Sistema de Blackboard

> **Definição:** A memória compartilhada da instância de IA.

---

## O Problema do "Acoplamento"

Sem um Blackboard, uma Task `ChasePlayer` precisaria:
1.  Procurar o node Player na cena (`get_tree().get_nodes_in_group...`).
2.  Guardar essa referência internamente.

Se outra Task `AttackPlayer` rodar depois, ela teria que **procurar de novo**. Ineficiente e sujo.

## A Solução Blackboard

O `MBTBlackboard` funciona como um quadro negro onde as Tasks escrevem e leem lembretes.

1.  Task `FindTarget` roda:
    - Escaneia a área.
    - Acha "Hero".
    - Escreve no Blackboard: `variable["target"] = Hero`.
2.  Task `Chase` roda:
    - Lê `variable["target"]`.
    - Move para a posição dele.
3.  Task `Attack` roda:
    - Lê `variable["target"]`.
    - Ativa habilidade nele.

As Tasks `Chase` e `Attack` **não sabem como o alvo foi encontrado**. Elas só sabem que ele está no quadro negro.

---

## Tipagem Estrita

Diferente de um `Dictionary` comum do GDScript, o Blackboard do MBT suporta (e encoraja) tipagem no Editor para evitar erros de runtime (ex: tentar mover para um `bool`).

Tipos suportados (C++ Variant):
- `BOOL`
- `INT`
- `FLOAT`
- `STRING` / `STRING_NAME`
- `VECTOR2` / `VECTOR3`
- `OBJECT` (Nodes, Resources)

---

## Escopos (Scopes)

Para evitar colisão de nomes em IAs complexas (ex: Squad AI), o Blackboard suporta hierarquia. (Feature Avançada).

- **Local Scope:** Variáveis desta árvore específica.
- **Global/Parent Scope:** Se a variável não é encontrada no Local, ele busca no Pai.
  - Útil para Squads: O Líder escreve `SquadTarget` no escopo Global. Todos os soldados leem `SquadTarget` para atacar o mesmo inimigo.

---

_Próximo: [Referência: Composites](05_Composites_Reference.md)_
