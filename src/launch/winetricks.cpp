#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
// linker claims the one time in launch.cpp was enough, we'll believe it
//#include "subprocess.hpp"

#include "bottles.hpp"
#include "launch.hpp"
#include "internal/launch.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::launch::winetricks(int argc, vector<string> argv) {
    if (argc == 1) {
        output::error("");
        return;
    }

    auto winetricks_argv = argv;
    winetricks_argv[0] = "winetricks";
    //output::statement(winetricks_str);
    launch::popen(winetricks_argv);

    if (bottles::active_bottle.config.find("winetricks") == bottles::active_bottle.config.end()) {
        bottles::active_bottle.config.emplace("winetricks", vector<string>());
    }
    for (string winetrick : winetricks_argv) {
        if (winetrick == "winetricks") { continue; }
        else if (winetrick.substr(0,1) == "-") { continue; } // opts don't get saved
        else { bottles::active_bottle.config["winetricks"].push_back(winetrick); }
    }

    bottles::active_bottle.save_config();
}
