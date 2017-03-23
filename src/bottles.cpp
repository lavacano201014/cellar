#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "bottles.hpp"
#include "fs.hpp"

using namespace std;

using json = nlohmann::json;

vector<string> cellar::bottles::list() {
	stringstream sstr_output;
	vector<string> result;

	string homepath = getenv("HOME");
	vector<string> homedir = cellar::fs::listdir(homepath);
	for (string item : homedir) {
		if (item.substr(0,5) == ".wine") {
			sstr_output << item;
			sstr_output << " ";
            
            string fullitem = homepath + "/" + item;
            boost::filesystem::file_status fullitem_status = boost::filesystem::symlink_status(fullitem);
            bool symlink = boost::filesystem::is_symlink(fullitem_status);

            if (symlink) {
                sstr_output << "- symlink to ";
                boost::filesystem::path realpath = boost::filesystem::canonical(fullitem);
                sstr_output << realpath.string();
                result.push_back(sstr_output.str());
                sstr_output.str("");
            } else {
			    string jsonpath = fullitem + "/cellar.json";
			    if (boost::filesystem::exists(jsonpath)) {
			    	try {
			    		json config;
			    		ifstream configstream(jsonpath);
			    		stringstream sstr_config;
			    		sstr_config << configstream.rdbuf();
			    		config = json::parse(sstr_config.str());

			    		sstr_output << "- " << config["name"];
			    		result.push_back(sstr_output.str());
			    		sstr_output.str(""); // clear it for the next item
			    	}
			    	catch (const exception &exc) {
			    		sstr_output << "- bogus cellar.json file";
			    		result.push_back(sstr_output.str());
			    		sstr_output.str("");
			    	}
			    }
			    else { 
			    	sstr_output << "- anonymous wine bottle";
			    	result.push_back(sstr_output.str());
			    	sstr_output.str("");
			    }
            }
		}
	}

	return result;
}
