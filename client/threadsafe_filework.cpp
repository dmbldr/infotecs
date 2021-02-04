#include "threadsafe_filework.h"

#include <mutex>
#include <string>

// TODO: исключения при неудачном открытии файла

void threadsafe_filework::push(const std::string& msg) {
    {   std::lock_guard<std::mutex> guard(_mtx);
        std::ofstream fout(_file_name);
        fout << msg;
    }
    _del_cond.notify_one();
}

std::string threadsafe_filework::wait_and_pop() {
    std::string res;
    std::unique_lock<std::mutex> guard(_mtx);
    _del_cond.wait(guard, [this]{return !empty();}); //TODO:безопасность от ложных пробуждений
    std::ifstream fin(_file_name);
    std::getline(fin, res);
    std::ofstream fout(_file_name, std::ofstream::trunc);
    return res;
}

bool threadsafe_filework::empty() const {
    std::ifstream file(_file_name);
    if(file.peek() == EOF) return true;
    return false;
}
