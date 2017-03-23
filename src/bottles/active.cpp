#include <iostream>

#include "bottles.hpp"
#include "internal/bottles.hpp"
#include "dll.hpp"

using namespace std;

DLL_PUBLIC void cellar::bottles::print_active_bottle(int argc, char** argv) {
    cout << "i just want to make sure cmake likes it first" << endl;
}
