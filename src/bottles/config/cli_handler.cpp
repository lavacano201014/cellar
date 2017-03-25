#include <string>
#include <vector>

#include "bottles.hpp"
#include "internal/bottles.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;
using namespace cellar::bottles;

using json = nlohmann::json;

void cellar::bottles::config_command(int argc, vector<string> argv) {
    if (argc == 1) {
        output::error("not enough arguments");
        return;
    }
    string command = argv[1];

    output::statement(command);
}
