#include <string>
#include <vector>
#include <unistd.h>

#include <boost/algorithm/string/join.hpp>
#include "subprocess.hpp"

#include "launch.hpp"
#include "internal/launch.hpp"
#include "output.hpp"

using namespace std;
using namespace cellar;

void cellar::launch::launch_program(vector<string> args) {
    vector<string> wineargs = args;
    wineargs[0] = "wine";

    string winelaunch = boost::algorithm::join(wineargs, " ");
    auto wine = subprocess::Popen(winelaunch);
    wine.wait();
}

void cellar::launch::launch_command(int argc, vector<string> args) {
    if (argc == 1) {
        output::error("forgot to specify a command");
        return;
    }
    launch::launch_program(args);
}
