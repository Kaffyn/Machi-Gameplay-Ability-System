#ifndef MBT_BLACKBOARD_H
#define MBT_BLACKBOARD_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class MBTBlackboard : public RefCounted {
    GDCLASS(MBTBlackboard, RefCounted);

private:
    Dictionary data;

protected:
    static void _bind_methods();

public:
    MBTBlackboard();
    ~MBTBlackboard();

    void set_value(const StringName &p_key, const Variant &p_value);
    Variant get_value(const StringName &p_key, const Variant &p_default = Variant()) const;
    bool has_value(const StringName &p_key) const;
    void erase_value(const StringName &p_key);
    void clear();
};

#endif // MBT_BLACKBOARD_H
