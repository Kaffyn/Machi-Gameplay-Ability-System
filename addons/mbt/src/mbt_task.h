#ifndef MBT_TASK_H
#define MBT_TASK_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class MBTTask : public Resource {
    GDCLASS(MBTTask, Resource);

protected:
    static void _bind_methods();

public:
    enum Status {
        FRESH,
        RUNNING,
        FAILURE,
        SUCCESS
    };

    MBTTask();
    ~MBTTask();

    // Virtual methods for GDScript and C++ subclasses
    virtual void _enter();
    virtual void _exit();
    virtual int _tick(double p_delta);

    // Main API
    int execute(double p_delta);
    
private:
    Status status = FRESH;
};

VARIANT_ENUM_CAST(MBTTask::Status);

#endif // MBT_TASK_H
