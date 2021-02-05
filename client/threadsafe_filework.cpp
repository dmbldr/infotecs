#include "threadsafe_filework.h"

#include <mutex>
#include <string>

void threadsafe_filework::push(const std::string& msg) {
    {   std::lock_guard<std::mutex> guard(_mtx);
        std::ofstream fout(_file_name);
        if(!fout.is_open()) throw std::ios_base::failure("Error opening file: push");
        fout << msg;
        empty = false;
    }
    _del_cond.notify_one();
}

std::string threadsafe_filework::wait_and_pop() {
    std::string res;
    std::unique_lock<std::mutex> guard(_mtx);
    _del_cond.wait(guard, [this]{return !empty;});
    std::ifstream fin(_file_name);
    if(!fin.is_open()) throw std::ios_base::failure("Error opening file: wait_and_pop");
    std::getline(fin, res);
    fin.close();
    if(std::remove(_file_name.c_str())) throw std::ios_base::failure("Error delete file: wait_and_pop");
    empty = true;
    return res;
}

/*bool threadsafe_filework::empty() const {
    std::ifstream file(_file_name);
    if(!file.is_open()) throw std::ios_base::failure("Error opening file: empty");
    if(file.peek() == EOF) return true;
    return false;
}*/
