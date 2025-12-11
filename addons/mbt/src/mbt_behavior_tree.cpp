#include "mbt_behavior_tree.h"

using namespace godot;

void MBTBehaviorTree::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_root_task", "task"), &MBTBehaviorTree::set_root_task);
    ClassDB::bind_method(D_METHOD("get_root_task"), &MBTBehaviorTree::get_root_task);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "root_task", PROPERTY_HINT_RESOURCE_TYPE, "MBTTask"), "set_root_task", "get_root_task");
}

MBTBehaviorTree::MBTBehaviorTree() {
}

MBTBehaviorTree::~MBTBehaviorTree() {
}

void MBTBehaviorTree::set_root_task(const Ref<MBTTask> &p_task) {
    root_task = p_task;
}

Ref<MBTTask> MBTBehaviorTree::get_root_task() const {
    return root_task;
}
