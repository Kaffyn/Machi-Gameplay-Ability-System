#include "mbt_player.h"

using namespace godot;

void MBTPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_behavior_tree", "tree"), &MBTPlayer::set_behavior_tree);
    ClassDB::bind_method(D_METHOD("get_behavior_tree"), &MBTPlayer::get_behavior_tree);
    
    ClassDB::bind_method(D_METHOD("set_blackboard", "blackboard"), &MBTPlayer::set_blackboard);
    ClassDB::bind_method(D_METHOD("get_blackboard"), &MBTPlayer::get_blackboard);

    ClassDB::bind_method(D_METHOD("set_active", "active"), &MBTPlayer::set_active);
    ClassDB::bind_method(D_METHOD("get_active"), &MBTPlayer::get_active);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "behavior_tree", PROPERTY_HINT_RESOURCE_TYPE, "MBTBehaviorTree"), "set_behavior_tree", "get_behavior_tree");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "active"), "set_active", "get_active");
}

MBTPlayer::MBTPlayer() {
    active = true;
    blackboard.instantiate(); // Auto-create blackboard
}

MBTPlayer::~MBTPlayer() {
}

void MBTPlayer::_process(double p_delta) {
    if (!active || behavior_tree.is_null()) {
        return;
    }

    Ref<MBTTask> root = behavior_tree->get_root_task();
    if (root.is_valid()) {
        root->execute(p_delta);
    }
}

void MBTPlayer::set_behavior_tree(const Ref<MBTBehaviorTree> &p_tree) {
    behavior_tree = p_tree;
}

Ref<MBTBehaviorTree> MBTPlayer::get_behavior_tree() const {
    return behavior_tree;
}

void MBTPlayer::set_blackboard(const Ref<MBTBlackboard> &p_blackboard) {
    blackboard = p_blackboard;
}

Ref<MBTBlackboard> MBTPlayer::get_blackboard() const {
    return blackboard;
}

void MBTPlayer::set_active(bool p_active) {
    active = p_active;
    set_process(active);
}

bool MBTPlayer::get_active() const {
    return active;
}
