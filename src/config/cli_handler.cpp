#include <string>
#include <vector>

#include "tclap/CmdLine.h"

#include "bottles.hpp"
#include "cellar.hpp"
#include "internal/config.hpp"
#include "output.hpp"
#include "version.hpp"

using namespace std;
using namespace cellar;
using namespace cellar::bottles;

using json = nlohmann::json;

void cellar::config::config_command(int argc, vector<string> argv) {
    const string desc = "Change cellar configuration options";
    const string versionstr = version::short_version();
    TCLAP::CmdLine cmdparse(desc, ' ', versionstr, false);

    TCLAP::SwitchArg globalarg("g", "global", "Use global user configuration (~/.local/share/cellar/cellar.json)");
    cmdparse.add(globalarg);

    TCLAP::UnlabeledValueArg<string> commandarg("command", "", true, "get", "command");
    cmdparse.add(commandarg);

    TCLAP::UnlabeledValueArg<string> keyarg("key", "", true, "", "key");
    cmdparse.add(keyarg);

    TCLAP::UnlabeledValueArg<string> valarg("value", "", false, "", "value");
    cmdparse.add(valarg);

    cmdparse.parse(argv);

    bool global = globalarg.getValue();
    string command = commandarg.getValue();
    string key = keyarg.getValue();
    string value = valarg.getValue();

    // BULLSHIT: switch can't be used for strings, according to gcc
    if (command == "get") {
        if (argc < 3) {
            output::error("usage: " + argv[0] + " get <key>");
            return;
        }

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
