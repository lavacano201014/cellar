#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include <boost/algorithm/string.hpp>
#include "tclap/CmdLine.h"

#include "output.hpp"
#include "paths.hpp"
#include "version.hpp"
#include "internal/core.hpp"

using namespace std;
using namespace cellar;

string cellar::paths::translate(std::string in_path, bool lazy) {
    bool windows_input;

    static regex drive_letter_rgx(R"([a-zA-Z]:\\)");

    windows_input = regex_match(in_path.substr(0, 3), drive_letter_rgx);

    if (!lazy) {
        output::warning("non-lazy path translation is not implemented yet");
    }

    if (windows_input) {
        if (lazy) {
            if (boost::algorithm::to_lower_copy(in_path.substr(0,1)) != "z") {
                throw invalid_argument("lazy path translation isn't possible for drive letters other than Z:");
            }
            string out_path = in_path.substr(2, in_path.size() - 2);
            
            size_t slashpos = out_path.find("\\");
            while (slashpos != std::string::npos) {
                out_path.replace(slashpos, 1, "/");
                slashpos = out_path.find("\\");
            }

            return out_path;
        } else {
            return paths::resolve_drive_letter(in_path);
        }
    } else {
        // lazy
        string out_path = "Z:";
        out_path.append(in_path);

        size_t slashpos = out_path.find("/");
        while (slashpos != std::string::npos) {
            out_path.replace(slashpos, 1, "\\");
            slashpos = out_path.find("/");
        }

        return out_path;
    }
}

void cellar::core::translate_command(int argc, vector<string> argv) {
    TCLAP::CmdLine cmdparse("Translate a path from Windows to UNIX, or vice versa", ' ', version::short_version(), false);
    
    TCLAP::SwitchArg lazyarg("l", "lazy", "Lazy path translating - don't read symlinks, just assume / is mounted on Z:");
    cmdparse.add(lazyarg);

    TCLAP::UnlabeledMultiArg<string> pathargcollector("path", "Paths to translate.", true, "PATH");
    cmdparse.add(pathargcollector);

    cmdparse.parse(argv);

    bool lazy = lazyarg.getValue();
    vector<string> pathargs = pathargcollector.getValue();

    for (auto arg : pathargs) {
        cout << paths::translate(arg, lazy) << endl;
    }
}
