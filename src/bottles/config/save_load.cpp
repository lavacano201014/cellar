#include <fstream>
#include <sstream>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "bottles.hpp"

using namespace std;
using namespace cellar::bottles;

namespace fs = boost::filesystem;

using json = nlohmann::json;

bool Bottle::load_config() {
    string jsonpath = this->canonical_path + "/cellar.json";
    if (fs::exists(jsonpath)) {
        json config;
        ifstream configstream(jsonpath);
        stringstream sstr_config;
        sstr_config << configstream.rdbuf();
        config = json::parse(sstr_config.str());
           
        this->config = config;
        return true;
    }
    else {
        return false;
    }
}

bool Bottle::save_config() {
    string jsonpath = this->canonical_path + "/cellar.json";

    // backup the old config in case something bad happens
    if (fs::exists(jsonpath)) {
        fs::copy_file(jsonpath, jsonpath + ".old");

        // now make room for the new one
        fs::remove(jsonpath);
    }

    ofstream configstream(jsonpath);
    configstream << this->config.dump(4);
    return true;
}
