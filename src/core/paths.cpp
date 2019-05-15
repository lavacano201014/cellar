#include <exception>
#include <string>
#include <regex>

#include <boost/algorithm/string.hpp>

#include "output.hpp"
#include "paths.hpp"

using namespace cellar;

std::string cellar::paths::translate(std::string in_path, bool lazy) {
    bool posix_input;

    static std::regex drive_letter(R"([a-zA-Z]:\\)");

    posix_input = ! std::regex_match(in_path.substr(0, 3), drive_letter);

    if (!lazy) {
        output::warning("non-lazy path translation is not implemented yet");
    }

    if (posix_input) {
        // lazy
        if (boost::algorithm::to_lower_copy(in_path.substr(0,1)) != "z") {
            throw std::invalid_argument("lazy path translation isn't possible for drive letters other than Z:");
        }
        std::string out_path = in_path.substr(2, in_path.size() - 2);
        
        size_t slashpos = out_path.find("\\");
        while (slashpos != std::string::npos) {
            out_path.replace(slashpos, 1, "/");
            slashpos = out_path.find("\\");
        }

        return out_path;
    } else {
        // lazy
        std::string out_path = "Z:";
        out_path.append(in_path);

        size_t slashpos = out_path.find("/");
        while (slashpos != std::string::npos) {
            out_path.replace(slashpos, 1, "\\");
            slashpos = out_path.find("/");
        }

        return out_path;
    }
}
