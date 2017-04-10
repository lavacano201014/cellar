#include <cstdlib>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "bottles.hpp"
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
        if (bottlechoice.substr(0,6) == ".wine.") {
            output::statement("tip: cellar can add the \".wine.\" prefix automatically");
            bottlechoice.replace(0,6,"");
        }
       
        fullbottlepath = homepath + "/.wine." + bottlechoice;
    }

    if (!boost::filesystem::exists(fullbottlepath)) {
        output::error(bottlechoice + " doesn't exist");
        return;
    }

    fs::recursive_remove(fullbottlepath);
}
