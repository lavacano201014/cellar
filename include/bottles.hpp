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
                // public members
                bottle_type type;
                json config;
                string path;
                string canonical_path;
                
                // constructors
                Bottle();
                Bottle(string);
                
                // methods
                bool load_config();
                bool save_config();
                string get_config(string);
                bool set_config(string, string);
        };
		extern map<string, Bottle> get_bottles();
	}
}

#endif // __BOTTLES_HPP
