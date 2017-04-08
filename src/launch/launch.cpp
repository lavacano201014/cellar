#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <boost/algorithm/string.hpp>
#include "subprocess.hpp"

#include "launch.hpp"
#include "internal/launch.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::launch::launch_program(vector<string> args) {
    args[0] = "wine";
    launch::popen(args);
}

void cellar::launch::launch_command(int argc, vector<string> args) {
    if (argc == 1) {
        output::error("forgot to specify a command");
        return;
    }
    launch::launch_program(args);
}

void cellar::launch::popen(string argv) {
    output::warning("use of deprecated string based function", true);
    output::statement("launching program: " + argv, true);
    vector<string> argvsplit;
    boost::algorithm::split(argvsplit, argv, boost::is_any_of(" "));
    string exec = argvsplit[0];
    vector<string> subargv;
    for (int curarg = 1; curarg < argvsplit.size(); curarg++) {
        subargv.push_back(argvsplit[curarg]);
    }
    auto subproc = subprocess::popen(exec, subargv);
    cout << subproc.stdout().rdbuf();
    cerr << subproc.stderr().rdbuf();
}

void cellar::launch::popen(vector<string> argv) {
    output::statement("launching program: " + boost::algorithm::join(argv, " "), true);
    string exec = argv[0];
    vector<string> subargv;
    for (int curarg = 1; curarg < argv.size(); curarg++) {
        subargv.push_back(argv[curarg]);
    }
    auto subproc = subprocess::popen(exec, subargv);
    cout << subproc.stdout().rdbuf();
    cerr << subproc.stderr().rdbuf();
}
