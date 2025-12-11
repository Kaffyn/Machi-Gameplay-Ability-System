#ifndef MBT_PLAYER_H
#define MBT_PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include "mbt_behavior_tree.h"
#include "mbt_blackboard.h"

using namespace godot;

class MBTPlayer : public Node {
    GDCLASS(MBTPlayer, Node);

private:
    Ref<MBTBehaviorTree> behavior_tree;
    Ref<MBTBlackboard> blackboard;
    bool active;

protected:
    static void _bind_methods();

public:
    MBTPlayer();
    ~MBTPlayer();

    void _process(double p_delta) override;

    void set_behavior_tree(const Ref<MBTBehaviorTree> &p_tree);
    Ref<MBTBehaviorTree> get_behavior_tree() const;

    void set_blackboard(const Ref<MBTBlackboard> &p_blackboard);
    Ref<MBTBlackboard> get_blackboard() const;

    void set_active(bool p_active);
    bool get_active() const;
};

#endif // MBT_PLAYER_H
