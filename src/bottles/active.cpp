#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "bottles.hpp"
#include "internal/bottles.hpp"

using namespace std;
using namespace cellar::bottles;

void cellar::bottles::print_active_bottle(int argc, char** argv) {
    map<string, Bottle> bottlemap = get_bottles();
    if (bottlemap.find(".wine") == bottlemap.end()) { // not found
        cout << "no active wine bottle" << endl;
        return;
    }

    Bottle active_bottle = bottlemap[".wine"];
    string bottlepath = active_bottle.canonical_path;
    if (active_bottle.type == bottle_symlink) {
        cout << "symlink to ";
        string homedir = getenv("HOME");
        if (active_bottle.canonical_path.substr(0, homedir.length()) == homedir) {
            bottlepath.replace(0, homedir.length() + 1, ""); // should convert "/home/someone/.wine.example" to ".wine.example"
            active_bottle = bottlemap[bottlepath];
        } else {
            cout << active_bottle.canonical_path << endl;
            return;
        }
    }

    switch (active_bottle.type) {
        case bottle_anonymous:
            cout << "anonymous wine bottle at " << active_bottle.canonical_path << endl;
            return;
        case bottle_labelled:
            cout << active_bottle.config["name"] << " (~/" << bottlepath << ")";
            if (active_bottle.config.find("desc") != active_bottle.config.end()) {
                cout << " - " << active_bottle.config["desc"];
            }
            cout << endl;
            return;
        default:
            cout << "broken or unsupported wine bottle" << endl;
            return;
    }
}
