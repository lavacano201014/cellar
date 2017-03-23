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

using namespace std;
using namespace cellar::bottles;

using CommandFunction = cellar::commands::CommandFunction;
using json = nlohmann::json;

Bottle::Bottle() {
    // define a null bottle
    // strings handle themselves
    config = json({});
    type = bottle_anonymous;
}

DLL_PUBLIC map<string, Bottle> cellar::bottles::get_bottles() {
	map<string, Bottle> result;

	string homepath = getenv("HOME");
	vector<string> homedir = cellar::fs::listdir(homepath);
	for (string item : homedir) {
		if (item.substr(0,5) == ".wine") {
            Bottle output;

            string fullitem = homepath + "/" + item;
            output.path = fullitem;

            boost::filesystem::file_status fullitem_status = boost::filesystem::symlink_status(fullitem);
            bool symlink = boost::filesystem::is_symlink(fullitem_status);

            if (symlink) {
                boost::filesystem::path realpath = boost::filesystem::canonical(fullitem);
                output.canonical_path = realpath.string();
                output.type = bottle_symlink;
            } else {
                output.canonical_path = fullitem;
			    string jsonpath = fullitem + "/cellar.json";
			    if (boost::filesystem::exists(jsonpath)) {
			    	try {
			    		json config;
			    		ifstream configstream(jsonpath);
			    		stringstream sstr_config;
			    		sstr_config << configstream.rdbuf();
   			    		config = json::parse(sstr_config.str());
                        
                        output.config = config;
                        output.type = bottle_labelled;
			    	}
			    	catch (const exception &exc) {
                        output.type = bottle_error;
			    	}
			    }
			    else {
                    output.type = bottle_anonymous;
			    }
            }
		    result[item] = output;
        }
	}

	return result;
}

void cellar::bottles::print_bottles(int argc, vector<string> argv) {
    map<string, Bottle> bottles = get_bottles();

    for (auto item : bottles) {
        if (item.first == ".wine" || item.first == ".wine.template") {
            // .wine is considered to be "active", and .wine.template is used as a template
            // and therefore treated specially
            continue;
        }
        Bottle bottle = item.second;
        cout << item.first << " - ";
        switch (bottle.type) {
            case bottle_anonymous:
                cout << "anonymous wine bottle";
                break;
            case bottle_symlink:
                cout << "symlink to " << bottle.canonical_path;
                break;
            case bottle_labelled:
                cout << bottle.config["name"];
                break;
            default:
                cout << "broken or unsupported wine bottle";
        }
        cout << endl;
    }
}
