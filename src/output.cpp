#include <iostream>
#include <string>

#include "output.hpp"

void cellar::output::statement(std::string str_message) {
    std::cout << "* " << str_message << std::endl;
}
void cellar::output::warning(std::string str_message) {
    std::cerr << "* " << str_message << std::endl;
}
void cellar::output::error(std::string str_message) {
    std::cerr << "* " << str_message << std::endl;
}
