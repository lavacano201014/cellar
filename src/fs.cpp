#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "fs.hpp"
#include "output.hpp"

using namespace std;

vector<string> cellar::fs::listdir(string path) {
	vector<string> result;
    boost::filesystem::path cwd(path);
    boost::filesystem::directory_iterator iter_end;

    for (boost::filesystem::directory_iterator iter_cwd(cwd); iter_cwd != iter_end; ++iter_cwd) {
        try {
            string item = iter_cwd->path().filename().native();
			
			result.push_back(item);
        }
        catch (const exception& exc) {
            // TODO: better error handling
            cellar::output::error("[1;31mfuck[0m");
        }
    }
	return result;
}

