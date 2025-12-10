# 05. Referência: Composites

> **Função:** Controladores de Fluxo. Eles têm múltiplos filhos.

---

## 1. Sequence (`->`)

**Lógica:** "E... E... E..."
Executa os filhos sequencialmente até que **TODOS tenham Sucesso** ou **UM falhe**.

- **Sucesso:** Se o último filho retornar Sucesso.
- **Falha:** Se *qualquer* filho retornar Falha (a execução para imediatamente).
- **Running:** Se o filho atual retornar Running.

**Uso Comum:** Passos lógicos obrigatórios.
- Ex: `Verificar Munição` -> `Mirar` -> `Atirar`.
  - Se `Verificar Munição` falhar, ele NEM tenta mirar.

## 2. Selector (`?`)

**Lógica:** "Ou... Ou... Ou..." (Também chamado de Fallback).
Executa os filhos sequencialmente até que **UM tenha Sucesso** ou **TODOS falhem**.

- **Sucesso:** Se *qualquer* filho retornar Sucesso (a execução para imediatamente).
- **Falha:** Se o último filho retornar Falha (todos falharam).
- **Running:** Se o filho atual retornar Running.

**Uso Comum:** Prioridades de comportamento.
- Ex: `Se Defender` ? `Atacar` ? `Provocar`.
  - Tenta se defender. Se conseguir (Sucesso), ótimo, parou aí.
  - Se não precisou defender (Falha), tenta Atacar.
  - Se não pode atacar (Falha), Provoca.

## 3. Parallel (`||`)

**Lógica:** Executa **TODOS** os filhos "ao mesmo tempo" (no mesmo tick).

- **Policies:** Configurável.
  - *Success Policy:* Precisa que 1, Todos ou N filhos tenham sucesso?
  - *Failure Policy:* Falha se 1 falhar?

**Uso Comum:** Ações simultâneas.
- Ex: `Mirar` E `Falar Frase de Efeito` E `Carregar Arma`.
- Tudo acontece no mesmo frame (ou simulando paralelismo).

## 4. Random Selector / Sequence

Variações estocásticas.
- **Random Selector:** Escolhe UM filho aleatoriamente para tentar executar.
- **Random Sequence:** Executa todos, mas embaralha a ordem a cada tick.

**Uso Comum:** Deixar a IA menos previsível.
- Ex: `RandomSelector` -> `Passo p/ Esquerda`, `Passo p/ Direita`, `Grito`.

---

_Próximo: [Referência: Decorators](06_Decorators_Reference.md)_
