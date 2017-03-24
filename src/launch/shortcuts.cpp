#include <string>
#include <vector>

#include "launch.hpp"
#include "internal/launch.hpp"

using namespace std;

void cellar::launch::launch_winecfg(int argc, vector<string> argv) {
    // cheap alias for "cellar launch winecfg"
    vector<string> launchargs;
    launchargs.push_back("cellar launch");
    launchargs.push_back("winecfg");

    cellar::launch::launch_program(launchargs);
}

void cellar::launch::launch_regedit(int argc, vector<string> argv) {
    // cheap alias for "cellar launch regedit"
    vector<string> launchargs;
    launchargs.push_back("cellar launch");
    launchargs.push_back("regedit");

    if (argc > 1) { launchargs.push_back(argv[1]); }

    cellar::launch::launch_program(launchargs);
}
