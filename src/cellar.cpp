#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"

#include "bottles.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
	vector<string> bottles = cellar::bottles::list();
	for (string item : bottles) {
		cout << item << endl;
	}

	return 0;
}
