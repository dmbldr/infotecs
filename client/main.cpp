#include "processor.h"

#include <thread>

int main() {
    processor p;
    std::thread th1(&processor::run_in_process, std::ref(p));
    std::thread th2(&processor::run_out_process, std::ref(p));
    th1.join();
    th2.join();
    return 0;
}



