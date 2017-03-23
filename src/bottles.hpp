#ifndef __BOTTLES_HPP
#define __BOTTLES_HPP
#pragma once

#include <map>
#include <string>

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
		map<string, Bottle> get_bottles();
	}
}

#endif // __BOTTLES_HPP
