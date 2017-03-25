#include <iostream>
#include <string>
#include <unistd.h>

#include "ansicol.hpp"
#include "cellar.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar::output;

bool cellar::output::colors;

void cellar::output::detect_colors() {
    int tty = isatty(fileno(stdout));

    if (tty == 1) {
        colors = true;
    } else {
        colors = false;
    }
}

void cellar::output::statement(string str_message, bool verbose) {
    if (verbose and !cellar::verbose) { return; }

    if (colors) {
        cout << ansicol::green << " >";
        cout << ansicol::green_bold << "> ";
        cout << ansicol::reset;
    } else {
        cout << "STAT ";
    }
    
    cout << str_message << endl;
}
void cellar::output::statement(string str_message) { statement(str_message, false); }

void cellar::output::warning(string str_message, bool verbose) {
    if (verbose and !cellar::verbose) { return; }

    if (colors) {
        cerr << ansicol::yellow << " >";
        cerr << ansicol::yellow_bold << "> ";
        cerr << ansicol::reset;
    } else {
        cerr << "WARN ";
    }
    
    cerr << str_message << endl;
}
void cellar::output::warning(string str_message) { warning(str_message, false); }

void cellar::output::error(string str_message, bool verbose) {
    if (verbose and !cellar::verbose) { return; }

    if (colors) {
        cerr << ansicol::red << " >";
        cerr << ansicol::red_bold << "> ";
        cerr << ansicol::reset;
    } else {
        cerr << "ERR! ";
    }
    
    cerr << str_message << endl;
}
void cellar::output::error(string str_message) { error(str_message, false); }

