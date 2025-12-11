#include "mbt_blackboard.h"

using namespace godot;

void MBTBlackboard::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_value", "key", "value"), &MBTBlackboard::set_value);
    ClassDB::bind_method(D_METHOD("get_value", "key", "default"), &MBTBlackboard::get_value, DEFVAL(Variant()));
    ClassDB::bind_method(D_METHOD("has_value", "key"), &MBTBlackboard::has_value);
    ClassDB::bind_method(D_METHOD("erase_value", "key"), &MBTBlackboard::erase_value);
    ClassDB::bind_method(D_METHOD("clear"), &MBTBlackboard::clear);
}

MBTBlackboard::MBTBlackboard() {
}

MBTBlackboard::~MBTBlackboard() {
}

void MBTBlackboard::set_value(const StringName &p_key, const Variant &p_value) {
    data[p_key] = p_value;
}

Variant MBTBlackboard::get_value(const StringName &p_key, const Variant &p_default) const {
    if (data.has(p_key)) {
        return data[p_key];
    }
    return p_default;
}

bool MBTBlackboard::has_value(const StringName &p_key) const {
    return data.has(p_key);
}

void MBTBlackboard::erase_value(const StringName &p_key) {
    data.erase(p_key);
}

void MBTBlackboard::clear() {
    data.clear();
}
