#include <cstdlib>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "bottles.hpp"
#include "internal/bottles.hpp"
#include "launch.hpp"
#include "internal/launch.hpp"
#include "fs.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;
using namespace cellar::bottles;

using json = nlohmann::json;

void cellar::bottles::press(string exec, vector<string> args, bool noexec) {
    // ensure pressed installer directory exists
    string homedir = getenv("HOME");
    string datadir = homedir + "/.local/share/cellar";
    string presseddir = datadir + "/pressed";
    if (!boost::filesystem::exists(datadir)) { boost::filesystem::create_directory(datadir); }
    if (!boost::filesystem::exists(presseddir)) { boost::filesystem::create_directory(presseddir); }

    string filename = boost::filesystem::path(exec).filename().native();
    auto pressedpath = boost::filesystem::path(presseddir);
    string pressedfile = (pressedpath / filename).native();
    if (boost::filesystem::exists(pressedfile)) {
        output::warning("clobbering existing version of " + filename);
        boost::filesystem::remove(pressedfile);
    }
    boost::filesystem::copy(exec, pressedfile);

    vector<string> argv;
    argv.push_back("wine");
    argv.push_back(pressedfile);

    if (!noexec) { launch::popen(argv); }

    if (active_bottle.config.find("pressed") == active_bottle.config.end()) {
        json pressed;
        active_bottle.config["pressed"] = pressed;
    }

    active_bottle.config["pressed"].emplace(filename, args);
    active_bottle.save_config();
}

void cellar::bottles::press_command(int argc, vector<string> argv) {
    bool noexec = false;
    string exec;
    vector<string> subargv;
    int startarg = 1;
    if (argv[1] == "-n") {
        noexec = true;
        startarg = 2;
    }

    for (int curarg = startarg; curarg < argc; curarg++) {
        if (curarg == startarg) { exec = argv[curarg]; }
        else { subargv.push_back(argv[curarg]); }
    }

    press(exec, subargv, noexec);
}
