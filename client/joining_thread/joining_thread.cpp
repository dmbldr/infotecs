#include "joining_thread.h"

joining_thread::~joining_thread() noexcept {
    if(joinable())
        join();
}

bool joining_thread::joinable() const noexcept {
    return _t.joinable();
}

void joining_thread::join() {
    _t.join();
}