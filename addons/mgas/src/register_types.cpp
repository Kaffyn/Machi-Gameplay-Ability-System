#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

// Include Your Classes
#include "machi_ability_system_component.h"
#include "machi_gameplay_ability.h"
#include "machi_attribute_set.h"
#include "machi_gameplay_effect.h"
#include "mbt_task.h"
#include "mbt_behavior_tree.h"
#include "mbt_player.h"
#include "mbt_blackboard.h"

using namespace godot;

void initialize_mgas_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<MachiAbilitySystemComponent>();
    ClassDB::register_class<MachiGameplayAbility>();
    ClassDB::register_class<MachiGameplayEffect>();
    ClassDB::register_class<MachiAttributeSet>();

    ClassDB::register_class<MBTTask>();
    ClassDB::register_class<MBTBehaviorTree>();
    ClassDB::register_class<MBTPlayer>();
    ClassDB::register_class<MBTBlackboard>();
}

void uninitialize_mgas_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    // Initialization.
    GDExtensionBool GDE_EXPORT mgas_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_mgas_module);
        init_obj.register_terminator(uninitialize_mgas_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
