#include <cstdlib>
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

    // BULLSHIT: switch can't be used for strings, according to gcc
    if (command == "get") {
        if (argc < 3) {
            output::error("usage: " + argv[0] + " get <key>");
            return;
        }

        // TEMP
        string homedir = getenv("HOME");
        Bottle active_bottle = Bottle(homedir + "/.wine");
        active_bottle.load_config();

        string value = active_bottle.get_config(argv[2]);
        if (value != "") {
            output::statement(argv[2] + ": " + value);
        } else {
            output::error(argv[2] + " is not defined");
        }
    } else if (command == "set") {
        output::statement("usage: " + argv[0] + " set <key> <value>");
    } else {
        output::statement("usage is one of:");
        output::statement("\t" + argv[0] + " get <key>");
        output::statement("\t" + argv[0] + " set <key> <value>");
        return;
    }
}
