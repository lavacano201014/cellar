#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "cellar.hpp"
#include "internal/core.hpp"
#include "help.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::core::help_command(int argc, vector<string> argv) {
    vector<string> commands = list_commands();
    cellar::print_header();

    cout << endl; // TODO: cellar::output function for code clarity

    if (argc == 1) {
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
    } else {
        string command = argv[1];
        stringstream sstr;
        sstr << "cellar " << command << " - ";

        string desc = help::get_description(command);
        if (desc.empty()) { sstr << "no description is available."; }
        else { sstr << desc; }
        output::statement(sstr.str());

        cout << endl;

        string details = help::get_details(command);
        if (details.empty()) { output::statement("no details available."); }
        else {
            vector<string> detaillines;
            boost::split(detaillines, details, boost::is_any_of("\n"));

            for (string line : detaillines) { 
                if (!line.empty()) { output::statement(line); }
                else { cout << endl; }
            }
        }
    }
}
