#ifndef __CONFIG_HPP
#define __CONFIG_HPP
#pragma once

#include "nlohmann/json.hpp"

using nlohmann::json;

namespace cellar {
    namespace config {
        json get_default_config();

        extern json global_config;
        extern json compiled_config;
    }
}

#endif // __CONFIG_HPP
