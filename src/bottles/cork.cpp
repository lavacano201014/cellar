#include <cstdlib>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
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

void cellar::bottles::cork(string bottlearg, bool remove) {
    string bottlepath = resolve_bottle(bottlearg);
    // ensure bottle is corkable
    if (!boost::filesystem::exists(bottlepath + "/cellar.json")) {
        output::error("cannot cork anonymous (or nonexistent) wine bottles");
        return;
    }
    // ensure corked bottle directory exists
    string homedir = getenv("HOME");
    string datadir = homedir + "/.local/share/cellar";
    string corkdir = datadir + "/corked";
    string corkpath = corkdir + "/" + bottlearg + ".json";
    if (!boost::filesystem::exists(datadir)) { boost::filesystem::create_directory(datadir); }
    if (!boost::filesystem::exists(corkdir)) { boost::filesystem::create_directory(corkdir); }

    if (boost::filesystem::exists(corkpath)) {
        output::error("bottle " + bottlearg + " already corked");
        return;
    }

    boost::filesystem::copy(bottlepath + "/cellar.json", datadir + "/corked/" + bottlearg + ".json");

    if (remove) { fs::recursive_remove(bottlepath); }
}

void cellar::bottles::cork_command(int argc, vector<string> argv) { 
    if (argv[1] == "-k" || argv[1] == "--keep") { cork(argv[2], false); }
    else { cork(argv[1], true); }
}

void cellar::bottles::uncork(string bottlearg) {
    string homedir = getenv("HOME");
    string datadir = homedir + "/.local/share/cellar";
    if (!boost::filesystem::exists(datadir + "/corked/" + bottlearg + ".json")) {
        output::error("no bottle named " + bottlearg + " to uncork");
        return;
    }
    
    string bottlepath = resolve_bottle(bottlearg);
    if (boost::filesystem::exists(bottlepath)) {
        output::error("refusing to clobber existing bottle " + bottlearg);
        return;
    }

    output::statement("creating wine prefix at " + bottlepath, true);
    setenv("WINEPREFIX", bottlepath.c_str(), 1);
    vector<string> createargs = {"cellar create", bottlearg};
    create_bottle(2, createargs);
    boost::filesystem::copy(datadir + "/corked/" + bottlearg + ".json", bottlepath + "/cellar.json");

    active_bottle = Bottle(bottlepath);

    if (active_bottle.config.find("winetricks") != active_bottle.config.end()) {
        vector<string> winetrickery = active_bottle.config.at("winetricks");
        output::statement("running winetricks with args: " + boost::algorithm::join(winetrickery, " "));
        launch::winetricks(winetrickery.size(), winetrickery);
    }

    if (active_bottle.config.find("pressed") != active_bottle.config.end()) {
        auto presseddir = boost::filesystem::path(datadir + "/pressed");
        auto pressed = active_bottle.config.at("pressed");
        for (auto pressed_iter = pressed.begin(); pressed_iter != pressed.end(); pressed_iter++) {
            string exec = pressed_iter.key();
            vector<string> args = pressed_iter.value();

            output::statement("running pressed installer " + exec + " with arguments: " + boost::algorithm::join(args, " "), true);
            vector<string> subargv;
            subargv.push_back("wine");
            subargv.push_back((presseddir / exec).native());
            for (string arg : args) { subargv.push_back(arg); }
            launch::popen(subargv);
        }
    }
}

void cellar::bottles::uncork_command(int argc, vector<string> argv) { uncork(argv[1]); }
