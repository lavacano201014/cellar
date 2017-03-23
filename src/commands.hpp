#ifndef __COMMANDS_HPP
#define __COMMANDS_HPP
#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;
namespace cellar {
    namespace commands {
        typedef void (*CommandFunction)(int, char*[]);
        extern map<string, CommandFunction> command_map;

        void add_command(string, CommandFunction);
        vector<string> list_commands();
    }
}

#endif // __COMMANDS_HPP
