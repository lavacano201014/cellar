#include <string>
#include <vector>

#include "cellar.hpp"
#include "internal/core.hpp"

using namespace std;

void cellar::commands::help_command(int argc, vector<string> argv) {
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
