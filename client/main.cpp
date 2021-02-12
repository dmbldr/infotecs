#include "processor.h"

#include <thread>

int main() {
    processor p;
    interruptible_thread th1(&processor::run_in_process, std::ref(p));
    std::thread th2(&processor::run_out_process, std::ref(p));
    th2.join();
    th1.interrupt();
    return 0;
}



