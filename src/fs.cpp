#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "fs.hpp"
#include "output.hpp"

using namespace std;
using namespace boost;

vector<string> cellar::fs::listdir(string path) {
	vector<string> result;
    filesystem::path cwd(path);
    filesystem::directory_iterator iter_end;

    for (filesystem::directory_iterator iter_cwd(cwd); iter_cwd != iter_end; ++iter_cwd) {
        string item = iter_cwd->path().filename().native();
		
		result.push_back(item);
    }
	return result;
}

bool cellar::fs::recursive_copy(string src, string dst) {
    if (!filesystem::exists(dst)) {
        bool success = filesystem::create_directory(dst);
        if (!success) { return false; }
    }

    for (string itemrel : cellar::fs::listdir(src)) {
        string itemabs = src + "/" + itemrel;
        string targetabs = dst + "/" + itemrel;

        auto itemstat = filesystem::symlink_status(itemabs);

        if (filesystem::is_directory(itemstat)) { recursive_copy(itemabs, targetabs); }
        else if (filesystem::is_symlink(itemstat)) { 
            auto symlinkpath = filesystem::read_symlink(itemabs);
            filesystem::create_symlink(symlinkpath, targetabs);
        }
        else { filesystem::copy(itemabs, targetabs); }
    }

    return true;
}
