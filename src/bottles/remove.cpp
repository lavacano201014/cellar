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
    if (bottlechoice.substr(0,1) == "/" || bottlechoice.substr(0,1) == ".") { // absolute or relative path
        fullbottlepath = bottlechoice;
    } else if (bottlechoice.substr(0,1) == "~") { // "absolute" path in home directory, not expanded by the shell for some reason (i've seen some shit)
        // this is a naive replacement and will fail if the user tries something like ~nick/.wine
        // i'm figuring at that point if you're doing that, you'll also recognize if your shell
        // isn't actually expanding your path...
        bottlechoice.replace(0,1,getenv("HOME"));
        // or at least you'll think to use verbose mode to make sure it's loading the right directory
        output::warning("your shell didn't expand your given path properly, doing a naive replacement", true);
        fullbottlepath = bottlechoice;
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
