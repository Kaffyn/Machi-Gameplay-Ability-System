# Suite de Plugins do Machi
> **Engenharia de Jogos de Alta Performance para Godot Engine**

Bem-vindo à suíte oficial de ferramentas de desenvolvimento do Machi. Este repositório hospeda a arquitetura de próxima geração para jogos complexos, escaláveis e orientados a dados.

A suíte é composta por módulos independentes que funcionam em harmonia:

---

## 🏗️ 1. Machi Gameplay Ability System (MGAS)
**O "Corpo" do seu Jogo.**

Um framework C++ massivo (GDExtension) inspirado no *Unreal GAS*, mas desenhado nativamente para Godot.

- **Gameplay Tags:** Sistema hierárquico de tags para lógica semântica (`State.Dead`, `Element.Fire`).
- **Abilities:** Lógica encapsulada e reutilizável (Ataques, Magias, Consumíveis).
- **Attributes:** Stats numéricos com modificadores complexos e replicação multiplayer.
- **Effects:** A "cola" que aplica buffs, debuffs e dano.
- **Multiplayer:** Replicação de estado state-of-the-art com Rollback e Prediction.

📚 **[Documentação Oficial do MGAS](addons/mgas/docs/README.md)**
- [Arquitetura](addons/mgas/docs/01_Architecture.md)
- [API Reference](addons/mgas/docs/09_API_Reference.md)

---

## 🧠 2. Machi Behavior Tree (MBT)
**O "Cérebro" do seu Jogo.**

Uma implementação moderna de Behavior Trees focada em performance e UX.

- **Action Request Pattern:** A IA não "move" o personagem diretamente; ela envia *Requests* para o MGAS.
- **Editor Visual:** Debugger em tempo real e visualização de fluxo.
- **Integração Nativa:** Nodes de folha projetados para disparar *Abilities* do MGAS.
- **Alta Performance:** Execução em C++ otimizada para milhares de agentes.

📚 **[Documentação Oficial do MBT](addons/mbt/README.md)**
- [Arquitetura](addons/mbt/docs/02_Architecture.md)
- [Integração MGAS](addons/mbt/docs/08_MGAS_Integration.md)

---

## 🚀 Começando

### Instalação
1. Clone este repositório.
2. Compile as GDExtensions (Sinais de vida em `bin/`).
3. Abra o projeto no Godot 4.5+.

### Estrutura do Projeto
```video_game
res://
├── addons/
│   ├── mgas/       # O Sistema de Habilidades (C++)
│   └── mbt/        # O Sistema de Comportamento (C++)
├── bin/            # Bibliotecas Compiladas (.dll, .so)
├── src/            # Código Fonte C++
├── entities/       # Prefabs de Gameplay (Player, Enemies)
└── levels/         # Cenas de Teste
```

---
*Machi Technologies - Feito com ❤️ e C++*
