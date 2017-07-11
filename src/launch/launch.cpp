#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <boost/algorithm/string.hpp>
#include "subprocess.hpp"

#include "cellar.hpp"
#include "bottles.hpp"
#include "launch.hpp"
#include "internal/launch.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::launch::launch_program(vector<string> args) {
    string winepath = bottles::active_bottle.get_config("wine-path");
    if (winepath == "") { winepath = "wine"; } // lets assume wine is in PATH if there's no config for it
                                               // TODO: better support for compiled in defaults (cogrc?)

    args[0] = winepath;
    launch::popen(args);
}

void cellar::launch::launch_command(int argc, vector<string> args) {
    if (argc == 1) {
        output::error("forgot to specify a command");
        return;
    }
    launch::launch_program(args);
}

void cellar::launch::popen(vector<string> argv) {
    output::statement("launching program: " + boost::algorithm::join(argv, " "), true);
    if (!dryrun) {
        string exec = argv[0];
        vector<string> subargv;
        for (int curarg = 1; curarg < argv.size(); curarg++) {
            subargv.push_back(argv[curarg]);
        }
        auto subproc = subprocess::popen(exec, subargv);
        cout << subproc.stdout().rdbuf();
        cerr << subproc.stderr().rdbuf();
    }
}
