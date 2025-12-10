# 06. Referência: Decorators

> **Função:** Modificadores e Guardiões. Eles têm apenas UM filho.

---

## Lógica e Controle

### `Inverter` (NOT)
Inverte o resultado do filho.
- Filho Sucesso -> Retorna Falha.
- Filho Falha -> Retorna Sucesso.
- Filho Running -> Retorna Running.
- **Uso:** `Inverter` -> `InimigoVisivel`. (Significa: "Inimigo NÃO visível").

### `AlwaysSucceed` / `AlwaysFail`
Ignora o resultado do filho (exceto Running) e força um resultado.
- **Uso:** Em um Selector, se você tem uma task opcional que pode falhar mas você não quer que ela impeça o resto da árvore.

### `Repeat` / `Loop`
Executa o filho X vezes ou infinitamente.
- **Uso:** `Repeat(3)` -> `Disparar Tiro`. (Atira 3 vezes em rajada).

---

## Guardiões (Checks)

Estas tarefas impedem a execução do filho se a condição não for atendida.

### `BlackboardCheck`
Verifica o valor de uma variável no Blackboard.
- Opções: `IsSet`, `IsNotSet`, `Equal`, `NotEqual`, `Greater`, `Less`.
- **Uso:** `BlackboardCheck(Health < 30)` -> `Fugir`.

### `Cooldown`
Após o filho executar (com sucesso ou falha), este decorator bloqueia novas execuções por X segundos.
- **Uso:** Limitar frequência de falas ou uso de granadas.

---

## Específicos do MGAS

### `HasTag`
Verifica se o `AbilitySystemComponent` do dono possui certas Tags.
- **Uso:** `HasTag(Status.Stunned)` -> `Wait`. (Se estiver stunado, espere).

### `VerifyAbility`
Verifica se uma Habilidade pode ser ativada (custo, cooldown, tags) SEM ativá-la.
- **Uso:** `VerifyAbility(Ulti)` -> `Sequence(Tocar Som Épico, Ativar Ulti)`.

---

_Próximo: [Referência: Leaves](07_Leaves_Reference.md)_
