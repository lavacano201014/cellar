#ifndef __BOTTLES_HPP
#define __BOTTLES_HPP
#pragma once

#include <map>
#include <string>

#include "commands.hpp"
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace cellar {
	namespace bottles {
        enum bottle_type {
            bottle_error,
            bottle_anonymous,
            bottle_labelled,
            bottle_symlink
        };
        class Bottle {
            public:
                bottle_type type;
                json config;
                string path;
                string canonical_path;
                Bottle();
        };
		extern map<string, Bottle> get_bottles();
	}
    namespace commands {
        extern map<string, cellar::commands::CommandFunction> bottles_commands();
    }
}

#endif // __BOTTLES_HPP
