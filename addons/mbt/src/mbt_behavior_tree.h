#ifndef MBT_BEHAVIOR_TREE_H
#define MBT_BEHAVIOR_TREE_H

#include <godot_cpp/classes/resource.hpp>
#include "mbt_task.h"

using namespace godot;

class MBTBehaviorTree : public Resource {
    GDCLASS(MBTBehaviorTree, Resource);

private:
    Ref<MBTTask> root_task;

protected:
    static void _bind_methods();

public:
    MBTBehaviorTree();
    ~MBTBehaviorTree();

    void set_root_task(const Ref<MBTTask> &p_task);
    Ref<MBTTask> get_root_task() const;
};

#endif // MBT_BEHAVIOR_TREE_H
