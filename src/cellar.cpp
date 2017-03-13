#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "fs.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> homedir = cellar::fs::listdir(getenv("HOME"));
	for (string item : homedir) {
		cout << item;
		cout << " ";
	}
	cout << endl;
    return 0;
}
