#include "processor.h"

#include <thread>
#include <csignal>
#include <cstring>

int main() {
    struct sigaction act{};
    std::memset(&act, 0, sizeof(act));
    act.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &act, nullptr);

    processor p;
    interruptible_thread th1(&processor::run_in_process, std::ref(p));
    std::thread th2(&processor::run_out_process, std::ref(p));
    th2.join();
    th1.interrupt();
    return 0;
}



