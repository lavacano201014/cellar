#include <iostream>
#include <string>
#include <vector>

#include "bottles.hpp"
#include "internal/bottles.hpp"

using namespace std;

void cellar::bottles::switch_active_bottle(int argc, vector<string> argv) {
    cout << argv[0] << endl;
}
