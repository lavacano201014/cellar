#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cellar.hpp"
#include "internal/core.hpp"
#include "help.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::commands::help_command(int argc, vector<string> argv) {
    vector<string> commands = list_commands();
    cellar::print_header();

    cout << endl; // TODO: cellar::output function for code clarity

    output::statement("You have these commands:");
    stringstream sstr;
    for (string command : commands) {
        sstr << "\t" << command;
        
        string desc = help::get_description(command);
        if (!desc.empty()) {
            sstr << " - " << desc;
        }
        output::statement(sstr.str());
        sstr.str("");
    }
}
