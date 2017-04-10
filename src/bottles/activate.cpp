#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "bottles.hpp"
#include "internal/bottles.hpp"
#include "output.hpp"

using namespace std;
using namespace boost::filesystem;

void cellar::bottles::switch_active_bottle(int argc, vector<string> argv) {
    if (argc == 1) {
        output::error("forgot to specify a bottle to activate");
        return;
    }

    string homepath = getenv("HOME");                // /home/nick
    string bottlepath = homepath + "/.wine";         // /home/nick/.wine
    string targetpath = bottlepath + "." + argv[1];  // /home/nick/.wine.example

    file_status targetstatus = symlink_status(targetpath);
    if (!exists(targetstatus)) {
        output::error("target " + targetpath + " does not exist");
        return;
    }

    file_status bottlestatus = symlink_status(bottlepath);
    if (exists(bottlestatus)) {
        bool bottlesymlink = is_symlink(bottlestatus);
        if (!bottlesymlink) {
            output::error("refusing to clobber " + bottlepath + ": not a symlink");
            return;
        }
        remove(bottlepath);
    }

    // TODO: not blindly assume this will magically work
    try {
        create_symlink(targetpath, bottlepath);
    } catch (filesystem_error &exc) {
        output::error(exc.what());
        return;
    }
}
