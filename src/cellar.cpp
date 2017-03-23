#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"

#include "bottles.hpp"
#include "commands.hpp"

using namespace std;
using namespace cellar;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    vector<string> commands = commands::list_commands();
    cout << "cellar - bottle management tool for WINE connoisseurs" << std::endl;
    for (string item : commands) {
        cout << item << " has loaded" << endl;
    }
    return 0;
}
