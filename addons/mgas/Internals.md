# MGAS — Internals (GDExtension)

> **Propósito:** Guia para engenheiros que desejam entender ou estender o núcleo C++ do MGAS.

---

## 1. Estrutura de Diretórios C++

A codebase C++ é compilada com SCons e linkada à Godot via `godot-cpp`.

```text
mgas/
├── SConstruct              # Build script (Python/SCons)
├── src/                    # Código Fonte C++
│   ├── register_types.cpp  # Entry Point (GDExtension Init)
│   ├── ability_system.cpp  # Core Logic
│   └── tags/               # Tag System Implementation
├── godot-cpp/              # Submódulo C++ Bindings (Official)
└── addons/mgas/bin/        # Binários Compilados (.dll, .so)
```

## 2. Compilação (Workflow)

Para compilar o MGAS, você precisa de:
- Python 3.x + SCons
- Compilador C++ (MSVC no Windows, GCC/Clang no Linux/Mac)

```bash
# Debug Build (com símbolos)
scons platform=windows target=template_debug

# Release Build (otimizado)
scons platform=windows target=template_release
```

## 3. O Sistema de Tags (GameplayTags)

### O Problema
Comparar strings (`if tag == "Status.Debuff.Stun"`) é lento (O(N) chars).
Comparar Enums é rápido, mas não hierárquico e difícil de estender com mods.

### A Solução MGAS
As Tags são registradas em um `GameplayTagManager` singleton no C++.
Cada Tag recebe um ID único (Inteiro) e informações sobre seu Pai.

- **Storage:** `HashMap<StringName, TagID>`
- **Comparison:** `TagA.Matches(TagB)` é apenas `TagA.Index == TagB.Index`.
- **Hierarchy:** `TagA.HasTag(ParentTag)` verifica se o ParentIndex de A corresponde a B.

## 4. Gerenciamento de Memória (AttributeSet)

Para garantir acesso ultra-rápido aos atributos (Health, Armor), evitamos `Dictionary` ou `Map` no runtime crítico.
Usamos **Reflection de Macros C++** e offsets de memória.

```cpp
// Exemplo Simplificado
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class MySet : public MachiAttributeSet {
    GDCLASS(MySet, MachiAttributeSet);
public:
    UPROPERTY()
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(MySet, Health);
};
```

Quando um `GameplayEffect` diz "Modifique Health", o sistema calcula o offset de memória da propriedade `Health` dentro da classe `AttributeSet` e escreve diretamente no endereço de memória, evitando lookups de string.

## 5. Integração com Godot

### GDExtension Init
O arquivo `register_types.cpp` é onde a mágica acontece. Ele diz à Godot: "Ei, aqui estão novas classes nativas".

```cpp
void initialize_mgas_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
    
    ClassDB::register_class<MachiAbilitySystemComponent>();
    ClassDB::register_class<MachiGameplayAbility>();
    // ...
}
```

Isso faz com que `MachiAbilitySystemComponent` apareça na janela "Create New Node" do editor, indistinguível de um node nativo como `Sprite2D`.

---

_MGAS — Internals v1.0_
