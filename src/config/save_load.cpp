#include <fstream>
#include <sstream>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "cellar.hpp"
#include "bottles.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;
using namespace cellar::bottles;

namespace fs = boost::filesystem;

using json = nlohmann::json;

json cellar::global_config;
json cellar::compiled_config;

bool Bottle::load_config() {
    bool globalconfig = false;
    bool localconfig = false;
    string jsonpath = this->canonical_path + "/cellar.json";
    if (fs::exists(jsonpath)) {
        json config;
        ifstream configstream(jsonpath);
        stringstream sstr_config;
        sstr_config << configstream.rdbuf();
        config = json::parse(sstr_config.str());
           
        this->config = config;
        localconfig = true;
    }
    else {
        output::warning("local config for this bottle doesn't exist", true);
    }

    // Get path to global cellar.json
    // (which should be ~/.local/share/cellar/cellar.json unless the user set XDG_DATA_HOME)
    stringstream sstr_globalpath;
    char* xdgdir = getenv("XDG_DATA_HOME");
    if (xdgdir == nullptr || xdgdir == "") {
        sstr_globalpath << getenv("HOME") << "/.local/share/cellar";
    } else {
        sstr_globalpath << xdgdir << "/cellar";
    }
    sstr_globalpath << "/cellar.json";
    
    // see src/config/defaults.cpp.cog
    compiled_config = cellar::config::get_default_config();

    string globaljsonpath = sstr_globalpath.str();
    if (fs::exists(globaljsonpath)) {
        ifstream configstream(globaljsonpath);
        stringstream sstr_config;
        sstr_config << configstream.rdbuf();
        cellar::global_config = json::parse(sstr_config.str());

        globalconfig = true;
    } else {
        output::warning("global cellar config doesn't exist", true);
    }

    return localconfig || globalconfig; // should return true if either one of these do
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
    configstream.close();

    if (fs::exists(jsonpath + ".old")) {
        // at this point it should be safe to remove the old config
        fs::remove(jsonpath + ".old");
    }
    return true;
}

string Bottle::get_config(string key) {
    if (this->config.find(key) != this->config.end()) {
        return this->config[key];
    } else if (cellar::global_config.find(key) != cellar::global_config.end()) {
        return cellar::global_config[key];
    } else if (cellar::compiled_config.find(key) != cellar::compiled_config.end()) {
        return cellar::compiled_config[key];
    } else {
        return "";
    }
}

bool Bottle::set_config(string key, string value) {
    this->config[key] = value;
    this->save_config();
    return true;
}
