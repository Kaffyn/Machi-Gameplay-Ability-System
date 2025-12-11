#include "mbt_task.h"

using namespace godot;

void MBTTask::_bind_methods() {
    BIND_ENUM_CONSTANT(FRESH);
    BIND_ENUM_CONSTANT(RUNNING);
    BIND_ENUM_CONSTANT(FAILURE);
    BIND_ENUM_CONSTANT(SUCCESS);

    GDVIRTUAL_BIND(_enter);
    GDVIRTUAL_BIND(_exit);
    GDVIRTUAL_BIND(_tick, "delta");
}

MBTTask::MBTTask() {
}

MBTTask::~MBTTask() {
}

void MBTTask::_enter() {
    // Default implementation does nothing
}

void MBTTask::_exit() {
    // Default implementation does nothing
}

int MBTTask::_tick(double p_delta) {
    return SUCCESS; // Default to success
}

int MBTTask::execute(double p_delta) {
    if (status != RUNNING) {
        _enter();
    }

    int result = 0;
    if (GDVIRTUAL_CALL(_tick, p_delta, result)) {
        // GDScript override called
        status = (Status)result;
    } else {
        // C++ implementation
        status = (Status)_tick(p_delta);
    }

    if (status != RUNNING) {
        _exit();
    }

    return status;
}
