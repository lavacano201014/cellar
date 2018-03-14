#include <cstdlib>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "bottles.hpp"
#include "cellar.hpp"
#include "internal/bottles.hpp"
#include "fs.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::bottles::remove_bottle(int argc, vector<string> argv) {
    string homepath = getenv("HOME");
    string bottlechoice = argv[1];
    string fullbottlepath;
    if (bottlechoice.substr(0,1) == "/" || bottlechoice.substr(0,1) == "." || bottlechoice.substr(0,1) == "~") { // absolute or relative path
        output::error("paths not accepted");
        return;
    } else {
        fullbottlepath = homepath + "/.local/share/cellar/bottles/" + bottlechoice;
    }

    if (!boost::filesystem::exists(fullbottlepath)) {
        output::error(bottlechoice + " doesn't exist");
        return;
    }

    output::statement("removing " + fullbottlepath, true);
    if (!dryrun) { fs::recursive_remove(fullbottlepath); }
}
