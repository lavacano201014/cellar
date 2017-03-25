#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "bottles.hpp"
#include "internal/bottles.hpp"
#include "dll.hpp"
#include "fs.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;
using namespace cellar::bottles;

using CommandFunction = cellar::commands::CommandFunction;
using json = nlohmann::json;

Bottle::Bottle() {
    // define a null bottle
    // strings handle themselves
    config = json({});
    type = bottle_anonymous;
}

Bottle::Bottle(string patharg) {
    output::statement("loading bottle from " + patharg, true);
    config = json({});
    path = patharg;
    
    boost::filesystem::file_status path_status = boost::filesystem::symlink_status(path);
    bool symlink = boost::filesystem::is_symlink(path_status);

    if (symlink) {
        boost::filesystem::path realpath = boost::filesystem::canonical(path);
        canonical_path = realpath.string();
        type = bottle_symlink;
    } else {
        canonical_path = path;
		try {
            if (load_config()) {
                type = bottle_labelled;
            } else {
                type = bottle_anonymous;
            }
    	}
		catch (const exception &exc) {
            type = bottle_error;
		}
    }
}

DLL_PUBLIC map<string, Bottle> cellar::bottles::get_bottles() {
	map<string, Bottle> result;

	string homepath = getenv("HOME");
	vector<string> homedir = fs::listdir(homepath);
	for (string item : homedir) {
		if (item.substr(0,5) == ".wine") {
            string fullitem = homepath + "/" + item;
            Bottle output(fullitem);

		    result[item] = output;
        }
	}

	return result;
}

void cellar::bottles::print_bottles(int argc, vector<string> argv) {
    map<string, Bottle> bottles = get_bottles();

    stringstream outstr;

    for (auto item : bottles) {
        if (item.first == ".wine" || item.first == ".wine.template") {
            // .wine is considered to be "active", and .wine.template is used as a template
            // and therefore treated specially
            continue;
        }
        Bottle bottle = item.second;
        outstr << item.first << " - ";
        switch (bottle.type) {
            case bottle_anonymous:
                outstr << "anonymous wine bottle";
                break;
            case bottle_symlink:
                outstr << "symlink to " << bottle.canonical_path;
                break;
            case bottle_labelled:
                outstr << bottle.config["name"];
                break;
            default:
                outstr << "broken or unsupported wine bottle";
        }
        output::statement(outstr.str());
        outstr.str("");
    }
}
