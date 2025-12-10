#include "machi_attribute_set.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

MachiAttributeSet::MachiAttributeSet() {
}

MachiAttributeSet::~MachiAttributeSet() {
}

void MachiAttributeSet::_bind_methods() {
    // GDVIRTUAL_BIND(_pre_attribute_change, "attribute", "new_value");
    // GDVIRTUAL_BIND(_post_attribute_change, "attribute", "old_value", "new_value");
}

void MachiAttributeSet::pre_attribute_change(const StringName &attribute, float &new_value) {
    // MVP: Simplified logic to bypass GDVIRTUAL macro compilation issues.
    // In production, restore GDVIRTUAL_CALL for performance.
    
    // Check if script has method
    if (has_method("_pre_attribute_change")) {
         new_value = call("_pre_attribute_change", attribute, new_value);
    }
}

void MachiAttributeSet::post_attribute_change(const StringName &attribute, float old_value, float new_value) {
    if (has_method("_post_attribute_change")) {
        call("_post_attribute_change", attribute, old_value, new_value);
    }
}
