#include "threadsafe_filework.h"

#include <mutex>
#include <string>

threadsafe_filework::~threadsafe_filework() {
    std::remove(_file_name.c_str());
}

void threadsafe_filework::try_push(std::string const& msg) {
    {   std::lock_guard<std::mutex> guard(_mtx);
        if(!_empty) throw std::ios_base::failure("Error push in file: file not empty");
        std::ofstream fout(_file_name);
        if(!fout.is_open()) throw std::ios_base::failure("Error opening file: push");
        fout << msg;
        _empty = false;
    }
    _del_cond.notify_one();
}

std::string threadsafe_filework::wait_and_pop() {
    std::string res;
    std::unique_lock<std::mutex> guard(_mtx);
    _del_cond.wait(guard, [this]{return !_empty;});
    std::ifstream fin(_file_name);
    if (!fin.is_open()) throw std::ios_base::failure("Error opening file: wait_and_pop");
    std::getline(fin, res);
    fin.close();
    if (std::remove(_file_name.c_str())) throw std::ios_base::failure("Error delete file: wait_and_pop");
    _empty = true;
    return res;
}
