#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "json.hpp"

#include "fs.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
	string homepath = getenv("HOME");
	vector<string> homedir = cellar::fs::listdir(homepath);
	for (string item : homedir) {
		if (item.substr(0,5) == ".wine") {
			cout << item;
			cout << " ";

			string jsonpath = homepath + "/" + item + "/cellar.json";
			if (boost::filesystem::exists(jsonpath)) {
				try {
					json config;
					ifstream configstream(jsonpath);
					stringstream sstr;
					sstr << configstream.rdbuf();
					config = json::parse(sstr.str());
	
					cout << "has a json" << endl;
				}
				catch (const exception &exc) {
					cout << "- bogus cellar.json file" << endl;
				}
			}
			else { cout << "- anonymous wine bottle" << endl; }
		}
	}
	cout << endl;
    return 0;
}
