#include <iostream>

#include "commands.hpp"
#include "cellar.hpp"

using namespace std;
using namespace cellar::commands;

map<string, CommandFunction> cellar::commands::command_map;

vector<string> cellar::commands::list_commands() {
    vector<string> result;
    for (auto& item : command_map) {
        result.push_back(item.first);
    }
    return result;
}

void help_command(int argc, char** argv) {
    vector<string> commands = list_commands();
    cellar::print_header();

    cout << "You have these commands:\n" << endl;

    int num_columns = 4;
    int cur_column = 1;
    for (string command : commands) {
        cout << "\t" << command;
        if (cur_column == num_columns) {
            cout << endl;
            cur_column = 1;
        } else {
            cur_column++;
        }
    }
    cout << endl;
}
CommandFunction helpcmd = command_map["help"] = &help_command;
