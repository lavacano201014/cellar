#include <iostream>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
    fs::path cwd(fs::current_path());
	cwd = fs::system_complete(".");
    fs::directory_iterator iter_end;

    for (fs::directory_iterator iter_cwd(cwd); iter_cwd != iter_end; ++iter_cwd) {
        try {
            std::string item = iter_cwd->path().filename().native();

            std::cout << item;
            std::cout << " ";
        }
        catch (const std::exception& exc) {
            std::cout << "[1;31mfuck[0m" << std::endl;
            return 1;
        }
    }
    std::cout << std::endl;
    return 0;
}
