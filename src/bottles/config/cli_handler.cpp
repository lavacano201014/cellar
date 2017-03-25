#include <string>
#include <vector>

#include "bottles.hpp"
#include "cellar.hpp"
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

        string key = argv[2];
        string value = active_bottle.get_config(key);
        
        if (value != "") {
            output::statement(key + ": " + value);
        } else {
            output::error(key + " is not defined");
        }
    } else if (command == "set") {
        if (argc < 4) {
            output::statement("usage: " + argv[0] + " set <key> <value>");
            return;
        }

        string key = argv[2];
        string newvalue = argv[3];
        string oldvalue = active_bottle.get_config(key);

        if (active_bottle.set_config(key, newvalue)) {
            output::statement(key + ": " + newvalue + " (was " + oldvalue + ")");
        } else {
            output::error(key + ": " + oldvalue);
        }
    } else {
        output::statement("usage is one of:");
        output::statement("\t" + argv[0] + " get <key>");
        output::statement("\t" + argv[0] + " set <key> <value>");
        return;
    }
}
