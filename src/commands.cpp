#include "commands.hpp"

using namespace std;
using namespace cellar::commands;

map<string, CommandFunction> cellar::commands::command_map;

bool cellar::commands::add_command(string name, CommandFunction func) {
    command_map[name] = func;
    return true;
}

vector<string> cellar::commands::list_commands() {
    vector<string> result;
    for (auto& item : command_map) {
        result.push_back(item.first);
    }
    return result;
}
