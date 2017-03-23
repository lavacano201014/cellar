#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"

#include "bottles.hpp"

using namespace std;
using namespace cellar;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
	map<string, bottles::Bottle> bottles = bottles::get_bottles();
	for (auto& item : bottles) {
        cout << item.first << "- ";
        bottles::Bottle current = item.second;

        switch (current.type) {
            case bottles::bottle_anonymous:
                cout << "anonymous wine bottle";
                break;
            case bottles::bottle_labelled:
                cout << current.config["name"];
                break;
            case bottles::bottle_symlink:
                cout << "symlink to ";
                cout << current.canonical_path;
                break;
            default:
                cout << "broken or unsupported wine bottle";
        }
        
        cout << endl;
	}

	return 0;
}
