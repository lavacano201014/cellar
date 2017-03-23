#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "config.h"
#include "tclap/CmdLine.h"
#include "json.hpp"

#include "bottles.hpp"
#include "cellar.hpp"
#include "commands.hpp"
#include "version.hpp"

using namespace std;
using namespace cellar;
using json = nlohmann::json;

void cellar::print_header() {
    cout << "cellar - bottle management tool for WINE connoisseurs" << std::endl;
    cout << version::short_version() << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header();
        cout << "\n(try \"cellar help\" if you're confused)" << endl;
        return 0;
    }
    try {
        const string desc = "bottle management tool for WINE connoisseurs";
        const string versionstr = version::short_version();
        TCLAP::CmdLine cmdparse(desc, ' ', versionstr, false);
        TCLAP::UnlabeledValueArg<string> command("command", "Specific command to run.", true, "help", "command");
        cmdparse.add(command);

        cmdparse.parse(argc, argv);

        for (auto item : commands::bottles_commands()) {
            commands::command_map[item.first] = item.second;
        }

        string usercmd = command.getValue();
        if (commands::command_map.count(usercmd) > 0) {
            commands::command_map[usercmd](argc, argv);
        } else {
            cerr << "invalid command: " << usercmd << endl;
            return 1;
        }
        return 0;
    } catch (TCLAP::ArgException &exc) {
        cerr << "Invalid argument. (" << exc.argId() << ": " << exc.error() << ")" << endl;
        return 1;
    }
}
