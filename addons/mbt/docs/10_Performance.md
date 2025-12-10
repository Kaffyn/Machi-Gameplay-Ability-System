# 10. Performance e Escala

> **Meta:** 500 Zumbis a 60 FPS.

---

## O Custo da IA

Behavior Trees são leves, mas não são mágicas. O custo vem de:
1.  **Memory Thrashing:** Alocar/Desalocar memória a cada tick.
2.  **Tick Rate:** Rodar a árvore inteira a cada frame (60x/seg).
3.  **Sensor Queries:** Raycasts e Area scans dentro das Tasks.

## Soluções do MBT

### 1. Zero-Allocation Tick
O Engine C++ do MBT foi desenhado para **não alocar memória** durante o tick.
- Estruturas são alocadas na inicialização (Pool).
- O estado de execução (quais nós estão Running) é mantido em arrays fixos ou redimensionados raramente.

### 2. Time Slicing & Throttling (Planejado)
Não precisamos rodar a IA de um Zumbi distante 60 vezes por segundo.
O Componente `MBTPlayer` terá opções de **Update Interval**:
- `Every Frame` (Heroi, Boss)
- `0.1s` (Inimigos Próximos)
- `0.5s` (Inimigos Distantes)
- `No Tick` (Inimigos muito longe - Simulation LOD)

### 3. Event-Driven vs Polling
Sempre que possível, use Decorators que reagem a eventos (ex: Signals) em vez de checar condições a cada frame.
- O MGAS ajuda muito aqui. `WaitAbilityEnd` dorme a task e só acorda quando o sinal chega, custo zero de CPU enquanto espera.

---

## Dicas para o Dev

- **Cuidado com GDScript nas Leaves:** Se você tiver 1000 inimgos rodando uma Task GDScript pesada, o gargalo será o Script, não a Árvore C++.
- **Use Composites Nativos:** Abuse de `Sequence` e `Selector` nativos, eles são praticamente gratuitos em performance.
- **Cache Blackboard keys:** Strings são rápidas (StringName), mas acesso direto a objetos é mais rápido.

---

_Fim da Documentação._
