#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
// linker claims the one time in launch.cpp was enough, we'll believe it
//#include "subprocess.hpp"

#include "bottles.hpp"
#include "cellar.hpp"
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
    string winetricks_str = boost::algorithm::join(winetricks_argv, " ");
    //output::statement(winetricks_str);
    launch::popen(winetricks_str);

    if (cellar::active_bottle.config.find("winetricks") == cellar::active_bottle.config.end()) {
        cellar::active_bottle.config.emplace("winetricks", vector<string>());
    }
    for (string winetrick : winetricks_argv) {
        if (winetrick == "winetricks") { continue; }
        else if (winetrick.substr(0,1) == "-") { continue; } // opts don't get saved
        else { cellar::active_bottle.config["winetricks"].push_back(winetrick); }
    }

    cellar::active_bottle.save_config();
}
